/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penpalac <penpalac@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 14:46:22 by penpalac          #+#    #+#             */
/*   Updated: 2025/04/01 20:43:53 by penpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 *	type: PIPE
 *	token: |
 *	left: x
 *	right: y
 */

static char	*get_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	char	*tmp;
	int		i;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == NULL)
		i++;
	paths = ft_split(envp[i], ':');
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	i = 0;
	while (paths[i])
		free(paths[i++]);
	free(paths);
	return (NULL);
}

void	execute_cmd(t_ast *node, int fd_in, int fd_out, int is_last)
{
	pid_t	pid;
	char	*path;

	if (node->type != NODE_CMD)
		return ;
	pid = fork();
	if (pid == 0)
	{
		printf("CMD: %s\n", node->args[0]);
		printf("B - FDIN: %d, FDOUT: %d\n", fd_in, fd_out);
		if (fd_in != STDIN_FILENO)
		{
			if (dup2(fd_in, STDIN_FILENO) == -1)
			{
				perror("dup2 input failed");
				exit(EXIT_FAILURE);
			}
			close(fd_in);
		}
		if (fd_out != STDOUT_FILENO)
		{
			if (dup2(fd_out, STDOUT_FILENO) == -1)
			{
				perror("dup2 output failed");
				exit(EXIT_FAILURE);
			}
			close(fd_out);
		}
		printf("A - FDIN: %d, FDOUT: %d\n", fd_in, fd_out);
		path = get_path(node->args[0], node->envp);
		if (!path)
		{
			ft_error(node->args[0]);
			exit(127);
		}
		if (execve(path, node->args, node->envp) == -1)
		{
			ft_error("execve failed");
			free(path);
			exit(126);
		}
	}
	else if (pid > 0)
	{
		node->pid = pid;
		if (fd_in != STDIN_FILENO)
			close(fd_in);
		if (!is_last && fd_out != STDOUT_FILENO)
			close(fd_out);
	}
	else
		ft_error("fork failed");
}

void	handle_redirection(t_ast *redir, int *fd_in, int *fd_out)
{
	if (!redir)
		return ;
	if (redir->type == NODE_REDIR_OUT || redir->type == NODE_HEREDOC ||
		redir->type == NODE_REDIR_IN ||redir->type == NODE_REDIR_APPEND)
		{
			execute_redirection_node(redir, fd_in, fd_out);
		}
	if (redir->left->type != NODE_CMD)
		handle_redirection(redir->left, fd_in, fd_out);
}

void	execute_pipeline(t_ast *node, int fd_in, int fd_out)
{
	int	pipe_fd[2];
	int	new_fd_in;
	int	new_fd_out;

	if (pipe(pipe_fd) == -1)
	{
		perror("pipe failed");
		exit(EXIT_FAILURE);
	}
	if (node->left)
	{
		if (node->left->type == NODE_PIPE)
		{
			execute_pipeline(node->left, fd_in, pipe_fd[1]);
			close(pipe_fd[1]);
		}
		else
		{
			new_fd_in = fd_in;
			new_fd_out = pipe_fd[1]; // should be 6, when there's a redirection it changes to 7? tecnicamente funciona
			printf("FDs in left: %d, %d\n",new_fd_in, new_fd_out);
			// Handle redirections for the left side command
			if (node->left->type == NODE_HEREDOC
				|| node->left->type == NODE_REDIR_IN
				|| node->left->type == NODE_REDIR_OUT
				|| node->left->type == NODE_REDIR_APPEND)
			{
				handle_redirection(node->left, &new_fd_in, &new_fd_out);
				printf("FDs in left after redir: %d, %d\n",new_fd_in, new_fd_out);
				if (node->left->left && node->left->left->type == NODE_CMD)
					execute_cmd(node->left->left, new_fd_in, new_fd_out, 0);
			}
			else if (node->left->type == NODE_CMD)
				execute_cmd(node->left, new_fd_in, new_fd_out, 0);
			if (new_fd_in != STDIN_FILENO)
				close(new_fd_in);
		}
	}
	close(pipe_fd[1]);
	// Process right side (input comes from pipe)
	if (node->right)
	{
		new_fd_in = pipe_fd[0];
		new_fd_out = fd_out;
		printf("FDs in right: %d, %d\n",new_fd_in, new_fd_out);
		// Handle redirections for the right side command
		if (node->right->type == NODE_HEREDOC
			|| node->right->type == NODE_REDIR_IN
			|| node->right->type == NODE_REDIR_OUT
			|| node->right->type == NODE_REDIR_APPEND)
		{
			handle_redirection(node->right, &new_fd_in, &new_fd_out);
			if (new_fd_out == pipe_fd[1])
				new_fd_out = STDOUT_FILENO;
			printf("FDs in right after redir: %d, %d\n",new_fd_in, new_fd_out);
			if (node->right->left && node->right->left->type == NODE_CMD)
				execute_cmd(node->right->left, new_fd_in, new_fd_out, 1);
		}
		else if (node->right->type == NODE_CMD)
			execute_cmd(node->right, new_fd_in, new_fd_out, 1);
		close(new_fd_in);
	}
	close(pipe_fd[0]);
}

void	execute_pipe_node(t_ast *node, int *fd_in, int *fd_out)
{
	int	original_in;
	int	original_out;

	if (!node)
		return ;
	original_in = *fd_in;
	original_out = *fd_out;
	execute_pipeline(node, *fd_in, *fd_out);
	while (wait(NULL) > 0)
		;
}

// void	execute_pipeline(t_ast *node, int *fd_in, int *fd_out)
// {
// 	int		fd[2];
// 	int		prev_fd;
// 	int		status;
// 	int		i;
// 	t_ast	*temp;
// 	t_ast	*current;
// 	prev_fd = *fd_in;
// 	current = node;
// 	i = 0;
// 	while (current && current->type == NODE_PIPE)
// 	{
// 		if (pipe(fd) == -1)
// 		{
// 			perror("pipe failed");
// 			exit(EXIT_FAILURE);
// 		}
// 		if (current->right)
// 		{
// 			if (current->right->type == NODE_CMD)
// 			{
// 				printf("%s cmd exec\n", node->args[0]);
// 				execute_cmd(node, *fd_in, *fd_out, 0);
// 				close(fd[1]);
// 				if (prev_fd != *fd_in)
// 					close(prev_fd);
// 				prev_fd = fd[0];
// 			}
// 			else
// 				add_cmds_from_redir(current->right, &i, fd_in, fd_out);
// 		}
// 		if (current->left && (current->left->type == NODE_REDIR_OUT
// 				|| current->left->type == NODE_REDIR_APPEND
// 				|| current->left->type == NODE_REDIR_IN
// 				|| current->left->type == NODE_HEREDOC))
// 			add_cmds_from_redir(current->left, &i, fd_in, fd_out);
// 		current = current->left;
// 	}
// 	if (current && current->type == NODE_CMD)
// 	{
// 		printf("Last cmd exec\n");
// 		execute_cmd(node, *fd_in, *fd_out, 1);
// 		if (prev_fd != *fd_in)
// 			close(prev_fd);
// 	}
// 	while (wait(&status) > 0)
// 		;
// }

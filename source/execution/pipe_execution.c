/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penpalac <penpalac@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 14:46:22 by penpalac          #+#    #+#             */
/*   Updated: 2025/04/02 19:21:48 by penpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 *	type: PIPE
 *	token: |
 *	left: x
 *	right: y
 */

void	setup_redirections(t_ast *node)
{
	if (node->fd_infile != STDIN_FILENO)
	{
		dup2(node->fd_infile, STDIN_FILENO);
		close(node->fd_infile);
	}
	if (node->fd_outfile != STDOUT_FILENO)
	{
		dup2(node->fd_outfile, STDOUT_FILENO);
		close(node->fd_outfile);
	}
}

void	execute_command(t_ast *cmd, int fd_in, int fd_out)
{
	pid_t	pid;

	if (cmd->type == NODE_HEREDOC || cmd->type == NODE_REDIR_IN
		|| cmd->type == NODE_REDIR_OUT || cmd->type == NODE_REDIR_APPEND)
	{
		execute_redirection_node(cmd, &fd_in, &fd_out);
		if (cmd->left && cmd->left->type == NODE_CMD)
			cmd = cmd->left;
		else if (cmd->right && cmd->right->type == NODE_CMD)
			cmd = cmd->right;
	}
	pid = fork();
	if (pid == 0)
	{
		if (fd_in != STDIN_FILENO)
			dup2(fd_in, STDIN_FILENO);
		if (fd_out != STDOUT_FILENO)
			dup2(fd_out, STDOUT_FILENO);
		setup_redirections(cmd);
		if (fd_in != STDIN_FILENO)
			close(fd_in);
		if (fd_out != STDOUT_FILENO)
			close(fd_out);
		run_command(cmd);
	}
}

void	execute_pipeline(t_ast **cmds, int pipe_count, int *fd, int prev_fd)
{
	int	status;
	int	i;

	i = 0;
	while (i < pipe_count)
	{
		if (pipe(fd) == -1)
		{
			ft_error("Pipe");
			exit(EXIT_FAILURE);
		}
		execute_command(cmds[i], prev_fd, fd[1]);
		close(fd[1]);
		if (prev_fd != STDIN_FILENO)
			close(prev_fd);
		prev_fd = fd[0];
		i++;
	}
	execute_command(cmds[i], prev_fd, STDOUT_FILENO);
	if (prev_fd != STDIN_FILENO)
		close(prev_fd);
	while (wait(&status) > 0);
}

t_ast	**order_cmds(t_ast *node, t_ast **cmds)
{
	t_ast	*temp;
	t_ast	*current;
	int		i;
	int		j;

	i = 0;
	current = node;
	while (current && current->type == NODE_PIPE)
	{
		cmds[i++] = current->right;
		current = current->left;
	}
	cmds[i++] = current;
	cmds[i] = NULL;
	j = 0;
	while (j < i / 2)
	{
		temp = cmds[j];
		cmds[j] = cmds[i - 1 - j];
		cmds[i - 1 - j] = temp;
		j++;
	}
	return (cmds);
}

void	execute_pipe_node(t_ast *node)
{
	t_ast	**cmds;
	t_ast	*current;
	int		fd[2];
	int		prev_fd;
	int		pipe_count;

	prev_fd = STDIN_FILENO;
	current = node;
	pipe_count = 0;
	while (current && current->type == NODE_PIPE)
	{
		pipe_count++;
		current = current->left;
	}
	cmds = malloc((pipe_count + 2) * sizeof(t_ast *));
	if (!cmds)
		return ;
	cmds = order_cmds(node, cmds);
	execute_pipeline(cmds, pipe_count, fd, prev_fd);
	free(cmds);
}

/*

	int		pipe_fd[2];
	int		prev;
	int		i;
	t_ast	*current;

	i = 0;
	prev = -1;
	current = node;
	while (current && current->type == NODE_PIPE)
	{
		if (pipe(pipe_fd) == -1)
		{
			ft_error("Pipe");
			exit(EXIT_FAILURE);
		}
		if (current->left->type == NODE_PIPE)
			execute_pipe_node(current->left);
		else
			execute_command(current->left, prev, pipe_fd[1]);
		close(pipe_fd[1]);
		if (prev != -1)
			close(prev);
		prev = pipe_fd[0];
		current = current->right;
	}
		execute_command(current, prev, STDOUT_FILENO);
	if (prev != -1)
		close(prev);
	while (wait(NULL) > 0)
		;

*/

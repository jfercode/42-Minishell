/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaferna2 <jaferna2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:41:17 by jaferna2          #+#    #+#             */
/*   Updated: 2025/03/20 18:57:00 by jaferna2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * 	type: CMD
 *	token: echo
 * 	token arg[0]: echo
 *	token arg[1]: hello world
 */

char	*get_path(char **cmd, char **envp)
{
	char	**path;
	char	*tmp;
	int		i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	tmp = ft_substr(envp[i], 6, ft_strlen(envp[i]) + 1);
	path = ft_split(tmp, ':');
	if (!path)
		perror("Cmd");
	i = 0;
	while (path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		tmp = ft_strjoin(tmp, cmd[0]);
		if (access(tmp, F_OK | X_OK) == 0)
			return (tmp);
		i++;
	}
	free(tmp);
	return (NULL);
}

void	run_command(t_ast *node)
{
	char	*path;

    if (!node || !node->args || !node->args[0])
    {
        perror("Invalid command");
        exit(EXIT_FAILURE);
    }
	path = get_path(node->args, node->envp);
	if (!path)
	{
		perror("Command not found");
		exit(EXIT_FAILURE);
	}
	if (execve(path, node->args, node->envp) == -1)
	{
		perror("execve failed");
		exit(EXIT_FAILURE);
	}
}

/*
*	TO DO: Redireccion de entrada y de salida
*	
*/
void	execute_cmd_node(t_ast *node, int fd_in, int fd_out)
{
	// Execute cmd simple
	pid_t	pid;

	if (node->type != NODE_CMD)
		return ;
	pid = fork();
	if (pid == 0)
		run_command(node);
	else if (pid > 0)
	{
		node->pid = pid;
		waitpid(pid, NULL, 0);
	}
	else
		perror("fork");
}

/**
 *	type: PIPE
 *	token: |
 *	left: x
 *	right: y
 */

void	forking(t_ast *node, int fdin, int fdout)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("Error: fork failed");
		exit(1);
	}
	if (pid == 0)
	{
		if (fdin != STDIN_FILENO)
		{
			dup2(fdin, STDIN_FILENO);
			close(fdin);
		}
		if (fdout != STDOUT_FILENO)
		{
			dup2(fdout, STDOUT_FILENO);
			close(fdout);
		}
		run_command(node);
	}
}

void	execute_pipe_node(t_ast *node)
{
	// call pipe_function(x, y)
	int		fd[2];
	t_ast	*current;
	int		prev_fd;

	if (node->type != NODE_PIPE)
		return ; 
	prev_fd = STDIN_FILENO;
	current = node;
	while (current && current->type == NODE_PIPE)
	{
		if (pipe(fd) == -1)
		{
			perror("Error: pipe failed");
			return ;
		}
		if (current->left && current->left->type == NODE_CMD)
			forking(current->left, prev_fd, fd[1]);
		else
			execute_pipe_node(current->left);
		close(fd[1]);
		if (prev_fd != STDIN_FILENO)
			close(prev_fd);
		prev_fd = fd[0];
		current = current->right;
		if (current && current->type == NODE_CMD)
			forking(current, prev_fd, STDOUT_FILENO);
	}
	if (prev_fd != STDIN_FILENO)
		close(prev_fd);
	wait(NULL);
}

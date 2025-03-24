/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penpalac <penpalac@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 14:46:22 by penpalac          #+#    #+#             */
/*   Updated: 2025/03/24 14:41:30 by penpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 *	type: PIPE
 *	token: |
 *	left: x
 *	right: y
 */

static void	forking(t_ast *node, int fdin, int fdout)
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

void	execute_pipeline(t_ast **cmds, int pipe_count, int *fd, int prev_fd)
{
	int	status;
	int	i;

	i = 0;
	while (i < pipe_count)
	{
		if (pipe(fd) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		forking(cmds[i], prev_fd, fd[1]);
		close(fd[1]);
		if (prev_fd != STDIN_FILENO)
			close(prev_fd);
		prev_fd = fd[0];
		i++;
	}
	if (!cmds[i])
    	printf("Error: Last command in pipeline is NULL!\n");
	forking(cmds[i], prev_fd, STDOUT_FILENO);
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

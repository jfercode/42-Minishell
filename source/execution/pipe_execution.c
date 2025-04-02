/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penpalac <penpalac@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 14:46:22 by penpalac          #+#    #+#             */
/*   Updated: 2025/04/02 18:21:30 by penpalac         ###   ########.fr       */
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

void	execute_command(t_ast *cmd, int in_fd, int out_fd)
{
	pid_t	pid;

	if (cmd->type == NODE_HEREDOC || cmd->type == NODE_REDIR_IN
		|| cmd->type == NODE_REDIR_OUT || cmd->type == NODE_REDIR_APPEND)
	{
		execute_redirection_node(cmd, &in_fd, &out_fd);
		if (cmd->left && cmd->left->type == NODE_CMD)
			cmd = cmd->left;
		else if (cmd->right && cmd->right->type == NODE_CMD)
			cmd = cmd->right;
	}
	pid = fork();
	if (pid == 0)
	{
		if (in_fd != STDIN_FILENO)
			dup2(in_fd, STDIN_FILENO);
		if (out_fd != STDOUT_FILENO)
			dup2(out_fd, STDOUT_FILENO);
		setup_redirections(cmd);
		if (in_fd != STDIN_FILENO)
			close(in_fd);
		if (out_fd != STDOUT_FILENO)
			close(out_fd);
		run_command(cmd);
	}
}

void	execute_pipe_node(t_ast *node)
{
	int		pipe_fd[2];
	int		prev;
	t_ast	*current;

	prev = -1;
	current = node;
	while (current && current->type == NODE_PIPE)
	{
		if (pipe(pipe_fd) == -1)
		{
			ft_error("Pipe");
			exit(EXIT_FAILURE);
		}
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
}

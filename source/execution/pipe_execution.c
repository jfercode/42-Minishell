/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penpalac <penpalac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 14:46:22 by penpalac          #+#    #+#             */
/*   Updated: 2025/04/11 17:09:55 by penpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 *	type: PIPE
 *	token: |
 *	left: x
 *	right: y
 */

static void	fork_cmd(t_ast *cmd, int fd_in, int fd_out)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		setup_redirections(cmd, &fd_in, &fd_out);
		run_command(cmd);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			cmd->data->exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			cmd->data->exit_status = 128 + WTERMSIG(status);
		else
			cmd->data->exit_status = 1;
	}
	signal(SIGINT, ft_handle_sigint);
}

static void	execute_command(t_ast *cmd, int fd_in, int fd_out)
{
	int		fd;

	fd = 7;
	if (cmd->type == NODE_HEREDOC || cmd->type == NODE_REDIR_IN
		|| cmd->type == NODE_REDIR_OUT || cmd->type == NODE_REDIR_APPEND)
	{
		if (execute_redirection_node(cmd, &fd_in, &fd_out, &fd) == ERROR)
		{
			if (fd_in != STDIN_FILENO)
				close(fd_in);
			if (fd_out != STDOUT_FILENO)
				close(fd_out);
			return ;
		}
		while (cmd->left && (cmd->type != NODE_CMD))
			cmd = cmd->left;
	}
	signal(SIGINT, ft_handle_sigint_child);
	fork_cmd(cmd, fd_in, fd_out);
}

static void	execute_pipeline(t_ast **cmds, int pipe_count, int *fd, int prev_fd)
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
	while (wait(&status) > 0)
		;
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

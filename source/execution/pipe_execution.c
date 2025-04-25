/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaferna2 < jaferna2@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 14:46:22 by penpalac          #+#    #+#             */
/*   Updated: 2025/04/25 12:03:02 by jaferna2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 *	type: PIPE
 *	token: |
 *	left: x
 *	right: y
 */

static pid_t	fork_cmd(t_ast *cmd, int fd_in, int fd_out)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, ft_handle_sigint_bloq);
		setup_redirections(cmd, &fd_in, &fd_out);
		run_command(cmd);
	}
	else
		signal(SIGINT, ft_handle_sigint_pipes);
	return (pid);
}

static pid_t	execute_command(t_ast *cmd, int fd_in, int fd_out)
{
	int	fd;

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
			return (0);
		}
		while (cmd->left && (cmd->type != NODE_CMD))
			cmd = cmd->left;
	}
	return (fork_cmd(cmd, fd_in, fd_out));
}

static void	wait_for_children(pid_t *pids, t_ast **cmds, int count)
{
	int	status;

	while (count >= 0)
	{
		waitpid(pids[count], &status, 0);
		if (!cmds[count] || !cmds[count]->data)
			return ;
		if (WIFEXITED(status))
			cmds[count]->data->exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			cmds[count]->data->exit_status = 128 + WTERMSIG(status);
		else
			cmds[count]->data->exit_status = 1;
		count--;
	}
}

static void	execute_pipeline(t_ast **cmds, int pipe_count, int *fd, int prev_fd)
{
	pid_t	*pids;
	int		status;
	int		i;

	i = 0;
	pids = malloc((pipe_count + 1) * sizeof(pid_t));
	if (!pids)
		return (ft_error("Pid: Malloc failed"));
	while (i < pipe_count)
	{
		if (pipe(fd) == -1)
			ft_error_exit("Pipe: ");
		pids[i] = execute_command(cmds[i], prev_fd, fd[1]);
		close(fd[1]);
		if (prev_fd != STDIN_FILENO)
			close(prev_fd);
		prev_fd = fd[0];
		i++;
	}
	pids[i] = execute_command(cmds[i], prev_fd, STDOUT_FILENO);
	if (prev_fd != STDIN_FILENO)
		close(prev_fd);
	wait_for_children(pids, cmds, pipe_count);
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
	order_cmds(node, cmds);
	execute_pipeline(cmds, pipe_count, fd, prev_fd);
	free(cmds);
}

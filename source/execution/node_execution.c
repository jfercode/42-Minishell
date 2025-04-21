/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaferna2 < jaferna2@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 18:49:07 by jaferna2          #+#    #+#             */
/*   Updated: 2025/04/21 18:49:10 by jaferna2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Finds the full path of a command using the system's PATH
 * environment variable.
 *
 * Searches through each directory listed in the PATH environment variable,
 * appending the command name to each path, and checks if the command exists
 * using `access()`.
 *
 * Returns the first valid path found.
 *
 * Memory allocated for temporary paths is freed to prevent leaks.
 *
 * @param cmd  The command to find (e.g., "ls", "grep").
 * @param envp The environment variables containing the PATH.
 * @return The full path to the executable if found, or NULL if not found.
 */
char	*find_path(char *cmd, char **envp)
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

void	run_command(t_ast *node)
{
	char	*path;

	if (!node || !node->args || !node->args[0])
	{
		ft_error("Error: Invalid command");
		exit(127);
	}
	if (ft_strchr(node->args[0], '/'))
		path = ft_strdup(node->args[0]);
	else
		path = find_path(*node->args, node->data->envp);
	if (!path)
	{
		ft_error(node->args[0]);
		exit(127);
	}
	if (execve(path, node->args, node->data->envp) == -1)
	{
		ft_error("Error: Execve failed");
		free(path);
		exit(126);
	}
}

void	execute_cmd_node(t_ast *node)
{
	pid_t	pid;
	int		status;

	g_shell_mode = CMD;
	if (node->type != NODE_CMD)
		return ;
	if (is_builtin(node))
		node->data->exit_status = exec_builtin(node);
	else
	{
		pid = fork();
		if (pid == 0)
			run_command(node);
		else
		{
			waitpid(pid, &status, 0);
			if (WIFEXITED(status))
				node->data->exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				node->data->exit_status = 128 + WTERMSIG(status);
			else
				node->data->exit_status = 1;
		}
	}
	signal(SIGINT, ft_handle_sigint);
}

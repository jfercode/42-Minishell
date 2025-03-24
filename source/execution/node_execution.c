/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaferna2 <jaferna2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:41:17 by jaferna2          #+#    #+#             */
/*   Updated: 2025/03/24 12:02:47 by jaferna2         ###   ########.fr       */
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
		// exit(127);	
	}
	path = find_path(*node->args, node->envp);
	if (!path)
	{
		ft_error("Error: Command not found");
		// exit(127);
	}
	if (execve(path, node->args, node->envp) == -1)
	{
		ft_error("Error: Execve failed");
		free(path);
		// exit(126);
	}
}

void	execute_cmd_node(t_ast *node)
{
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
		ft_error("Error: Failed fork");
}

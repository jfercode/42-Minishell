/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penpalac <penpalac@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:41:17 by jaferna2          #+#    #+#             */
/*   Updated: 2025/03/24 14:26:15 by penpalac         ###   ########.fr       */
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
        exit(127);
    }
	path = get_path(node->args, node->envp);
	if (!path)
	{
		perror("Command not found");
		exit(127);
	}
	if (execve(path, node->args, node->envp) == -1)
	{
		perror("Execve failed");
		exit(127);
	}
}

/*
*	TO DO: Redireccion de entrada y de salida
*	
*/
void	execute_cmd_node(t_ast *node, int fd_in, int fd_out)
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
		perror("fork");
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabalons <pabalons@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:41:17 by jaferna2          #+#    #+#             */
/*   Updated: 2025/03/31 15:50:32 by pabalons         ###   ########.fr       */
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
	ft_execve(node);
	// {
	// 	perror("Command not found");
	// 	exit(EXIT_FAILURE);
	// }
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

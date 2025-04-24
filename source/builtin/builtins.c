/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penpalac <penpalac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 17:31:37 by penpalac          #+#    #+#             */
/*   Updated: 2025/04/24 18:01:27 by penpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	check_node_args(t_ast *node)
{
	int	res;

	res = 0;
	while (node->args[res])
		res++;
	return (res);
}

int	is_builtin(t_ast *node)
{
	if (ft_strncmp(node->args[0], "cd", ft_strlen(node->args[0])) == 0)
		return (1);
	else if (ft_strncmp(node->args[0], "echo", ft_strlen(node->args[0])) == 0)
		return (1);
	else if (ft_strncmp(node->args[0], "env", ft_strlen(node->args[0])) == 0)
		return (1);
	else if (ft_strncmp(node->args[0], "exit", ft_strlen(node->args[0])) == 0)
		return (1);
	else if (ft_strncmp(node->args[0], "export", ft_strlen(node->args[0])) == 0)
		return (1);
	else if (ft_strncmp(node->args[0], "pwd", ft_strlen(node->args[0])) == 0)
		return (1);
	else if (ft_strncmp(node->args[0], "unset", ft_strlen(node->args[0])) == 0)
		return (1);
	else
		return (0);
}

int	exec_builtin(t_ast *node)
{
	if (ft_strncmp(node->args[0], "cd", ft_strlen(node->args[0])) == 0)
		return (node->data->exit_status = ft_cd(node->args[1]));
	else if (ft_strncmp(node->args[0], "echo", ft_strlen(node->args[0])) == 0)
		return (node->data->exit_status = ft_echo(check_node_args(node),
				node->args));
	else if (ft_strncmp(node->args[0], "env", ft_strlen(node->args[0])) == 0)
		return (node->data->exit_status = ft_env(node));
	else if (ft_strncmp(node->args[0], "exit", ft_strlen(node->args[0])) == 0)
		return (node->data->exit_status = ft_exit(node));
	else if (ft_strncmp(node->args[0], "export", ft_strlen(node->args[0])) == 0)
		return (node->data->exit_status = ft_export(node));
	else if (ft_strncmp(node->args[0], "pwd", ft_strlen(node->args[0])) == 0)
		return (node->data->exit_status = ft_pwd());
	else if (ft_strncmp(node->args[0], "unset", ft_strlen(node->args[0])) == 0)
		return (node->data->exit_status = ft_unset(node->data->envp,
				node->args[1]));
	return (0);
}

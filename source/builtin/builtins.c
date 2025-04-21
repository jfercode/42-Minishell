/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaferna2 < jaferna2@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 17:31:37 by penpalac          #+#    #+#             */
/*   Updated: 2025/04/21 18:53:52 by jaferna2         ###   ########.fr       */
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
	if (ft_strncmp(node->args[0], "cd", 2) == 0)
		return (1);
	else if (ft_strncmp(node->args[0], "echo", 4) == 0)
		return (1);
	else if (ft_strncmp(node->args[0], "env", 3) == 0)
		return (1);
	else if (ft_strncmp(node->args[0], "exit", 4) == 0)
		return (1);
	else if (ft_strncmp(node->args[0], "export", 6) == 0)
		return (1);
	else if (ft_strncmp(node->args[0], "pwd", 3) == 0)
		return (1);
	else if (ft_strncmp(node->args[0], "unset", 5) == 0)
		return (1);
	else
		return (0);
}

int	exec_builtin(t_ast *node)
{
	if (ft_strncmp(node->args[0], "cd", 2) == 0)
		return (node->data->exit_status = ft_cd(node->args[1]));
	else if (ft_strncmp(node->args[0], "echo", 4) == 0)
		return (node->data->exit_status = ft_echo(check_node_args(node),
				node->args));
	else if (ft_strncmp(node->args[0], "env", 3) == 0)
		return (node->data->exit_status = ft_env(node));
	else if (ft_strncmp(node->args[0], "exit", 4) == 0)
		return (node->data->exit_status = ft_exit(node));
	else if (ft_strncmp(node->args[0], "export", 6) == 0)
		return (node->data->exit_status = ft_export(node));
	else if (ft_strncmp(node->args[0], "pwd", 3) == 0)
		return (node->data->exit_status = ft_pwd());
	else if (ft_strncmp(node->args[0], "unset", 5) == 0)
		return (node->data->exit_status = ft_unset(node->data->envp,
				node->args[1]));
	return (0);
}

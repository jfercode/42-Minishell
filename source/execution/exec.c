/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabalons <pabalons@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 18:06:20 by pabalons          #+#    #+#             */
/*   Updated: 2025/04/09 18:06:41 by pabalons         ###   ########.fr       */
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

int	check_token(char *str)
{
	char	*builtin_types[] = {"cd", "echo", "env", "exit", "export", "pwd",
			"unset", NULL};
	int		i;

	i = 0;
	while (builtin_types[i] != NULL)
	{
		if (ft_strncmp(str, builtin_types[i], ft_strlen(builtin_types[i])) == 0)
			return (i);
		i++;
	}
	return (-1);
}

int	ft_execve(t_ast *node)
{
	int token_checked;
	int num_args;

	if (!node)
	{
		ft_putstr_fd("No token provided\n", 2);
		return (1);
	}

	token_checked = check_token(node->args[0]);

	if (token_checked >= 0)
	{
		if (token_checked == 0)
			ft_cd(node->args[1]);
		else if (token_checked == 1)
			ft_echo(check_node_args(node), node->args);
		else if (token_checked == 2)
			ft_env();
		else if (token_checked == 3)
			ft_exit(node);
		else if (token_checked == 4)
			ft_export(node->args);
		else if (token_checked == 5)
			ft_pwd();
		else if (token_checked == 6)
			ft_unset(node->args[1]);
	}
	else if (token_checked == -1)
		return (1);
	else
	{
		ft_error_exit("Error checking token");
		return (1);
	}
	return (0);
}
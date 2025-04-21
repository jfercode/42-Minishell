/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaferna2 < jaferna2@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 18:06:20 by pabalons          #+#    #+#             */
/*   Updated: 2025/04/21 17:19:18 by jaferna2         ###   ########.fr       */
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

static char	**get_builtin_types(void)
{
	static char	*builitin_types[] = {
		"cd", "echo", "env", "exit", "export", "pwd", "unset", NULL
	};

	return (builitin_types);
}

int	check_token(char *str)
{
	char	**builtin_types;
	int		i;

	i = 0;
	builtin_types = get_builtin_types;
	while (builtin_types[i] != NULL)
	{
		if (ft_strncmp(str, builtin_types[i], ft_strlen(builtin_types[i])) == 0)
			return (i);
		i++;
	}
	return (-1);
}

static	int	check_token_exec(int tocken, t_ast *node)
{
	if (tocken >= 0)
	{
		if (tocken == 0)
			ft_cd(node->args[1]);
		else if (tocken == 1)
			ft_echo(check_node_args(node), node->args);
		else if (tocken == 2)
			ft_env();
		else if (tocken == 3)
			ft_exit(node);
		else if (tocken == 4)
			ft_export(node->args);
		else if (tocken == 5)
			ft_pwd();
		else if (tocken == 6)
			ft_unset(node->args[1]);
	}
	else if (tocken == -1)
		return (1);
	else
		ft_error_exit("Error checking token");
	return (0);
}

int	ft_execve(t_ast *node)
{
	int	token_checked;
	int	num_args;

	if (!node)
	{
		ft_putstr_fd("No token provided\n", 2);
		return (1);
	}
	token_checked = check_token(node->args[0]);
	return (check_token_exec(token_checked, node));
}

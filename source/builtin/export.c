/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabalons <pabalons@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 14:52:22 by pabalons          #+#    #+#             */
/*   Updated: 2025/04/09 17:50:11 by pabalons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_env(t_ast *node)
{
	int	i;

	i = 0;
	while (node->data->envp[i])
	{
		printf("declare -x %s\n", node->data->envp[i]);
		i++;
	}
}

int	set_env_var(t_ast *node, const char *var)
{
	char	*equal_sign;
	int		env_count;
	char	*existing_var;
	char	**new_envp;
	int		i;

	equal_sign = strchr(var, '=');
	if (!equal_sign)
	{
		printf("export: '%s' is not a valid identifier\n", var);
		ft_putstr_fd("export: '%s' is not a valid identifier\n", 2);
		return (1);
	}
	env_count = 0;
	while (node->data->envp[env_count] != NULL)
	{
		existing_var = node->data->envp[env_count];
		if (strncmp(existing_var, var, equal_sign - var) == 0
			&& existing_var[equal_sign - var] == '=')
		{
			node->data->envp[env_count] = strdup(var);
			return (0);
		}
		env_count++;
	}
	new_envp = malloc((env_count + 2) * sizeof(char *));
	if (!new_envp)
	{
		ft_error("Malloc");
		return (1);
	}
	i = 0;
	while (node->data->envp[i] != NULL)
	{
		new_envp[i] = node->data->envp[i];
		i++;
	}
	new_envp[i] = strdup(var);
	new_envp[i + 1] = NULL;
	node->data->envp = new_envp;
	return (0);
}

int	ft_export(t_ast *node)
{
	int	i;

	i = 1;
	if (!node->args[1])
	{
		print_env(node);
		return (0);
	}
	while (node->args[i] != NULL)
	{
		set_env_var(node, node->args[i]);
		i++;
	}
	return (0);
}

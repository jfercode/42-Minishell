/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaferna2 < jaferna2@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 14:52:22 by pabalons          #+#    #+#             */
/*   Updated: 2025/04/21 18:53:00 by jaferna2         ###   ########.fr       */
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
		return (ft_error("export"), 1);
	env_count = 0;
	while (node->data->envp[env_count] != NULL)
	{
		existing_var = node->data->envp[env_count];
		if (strncmp(existing_var, var, equal_sign - var) == 0
			&& existing_var[equal_sign - var] == '=')
			return (node->data->envp[env_count] = strdup(var), 0);
		env_count++;
	}
	new_envp = malloc((env_count + 2) * sizeof(char *));
	if (!new_envp)
		return (ft_error("Malloc"), 1);
	i = 0;
	while (node->data->envp[i++] != NULL)
		new_envp[i] = node->data->envp[i];
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabalons <pabalons@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 14:52:22 by pabalons          #+#    #+#             */
/*   Updated: 2025/05/01 15:17:03 by pabalons         ###   ########.fr       */
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

char	*check_and_replace(t_ast *node, const char *var, int env_count)
{
	char	*existing_var;

	existing_var = node->data->envp[env_count];
	if (ft_strncmp(existing_var, var, ft_strchr(var, '=') - var) == 0
		&& existing_var[ft_strchr(var, '=') - var] == '=')
	{
		free(node->data->envp[env_count]);
		node->data->envp[env_count] = ft_strdup(var);
		return (node->data->envp[env_count]);
	}
	else
		return (NULL);
}

int	set_env_var(t_ast *node, const char *var)
{
	char	**new_envp;
	int		env_count;
	int		i;

	if (ft_strchr(var, '=') == NULL)
		return (0);
	env_count = 0;
	while (node->data->envp[env_count] != NULL)
	{
		if (check_and_replace(node, var, env_count) != NULL)
			return (0);
		env_count++;
	}
	new_envp = malloc((env_count + 2) * sizeof(char *));
	if (!new_envp)
		return (ft_error("Malloc"), 1);
	i = -1;
	while (node->data->envp[++i] != NULL)
		new_envp[i] = node->data->envp[i];
	new_envp[i] = ft_strdup(var);
	new_envp[i + 1] = NULL;
	copy_envp(node->data, new_envp);
	free(new_envp[i]);
	free(new_envp);
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

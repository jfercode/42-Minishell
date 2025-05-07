/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penpalac <penpalac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 14:52:22 by pabalons          #+#    #+#             */
/*   Updated: 2025/05/07 16:44:44 by penpalac         ###   ########.fr       */
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

char	**set_env_var(t_ast *node, const char *var)
{
	char	**new_envp;
	int		env_count;
	int		i;

	if (ft_strchr(var, '=') == NULL)
		return (node->data->envp);
	env_count = 0;
	while (node->data->envp[env_count] != NULL)
	{
		if (check_and_replace(node, var, env_count) != NULL)
			return (node->data->envp);
		env_count++;
	}
	new_envp = malloc((env_count + 2) * sizeof(char *));
	if (!new_envp)
		return (ft_error("Malloc"), node->data->envp);
	i = -1;
	while (node->data->envp[++i] != NULL)
		new_envp[i] = ft_strdup(node->data->envp[i]);
	new_envp[i] = ft_strdup(var);
	new_envp[i + 1] = NULL;
	return (new_envp);
}

int	ft_export(t_ast *node)
{
	int		i;
	char	**tmp_env;
	char	**old_envp;

	i = 1;
	if (!node->args[1])
	{
		print_env(node);
		return (0);
	}
	while (node->args[i] != NULL)
	{
		old_envp = node->data->envp;
		tmp_env = set_env_var(node, node->args[i]);
		if (tmp_env != old_envp)
		{
			free_matrix(old_envp);
			node->data->envp = tmp_env;
		}
		i++;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabalons <pabalons@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 11:28:07 by pabalons          #+#    #+#             */
/*   Updated: 2025/03/03 11:28:07 by pabalons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern char	**environ;

void	print_env(void)
{
	int	i;

	i = 0;
	while (environ[i])
	{
		printf("%s\n", environ[i]);
		i++;
	}
}

int	set_env_var(const char *var)
{
	char	*equal_sign;
	int		env_count;
	char	*existing_var;
	char	**new_environ;
	int		i;

	equal_sign = strchr(var, '=');
	if (!equal_sign)
	{
		// Revisar el error
		printf("export: '%s' is not a valid identifier\n", var);
		ft_putstr_fd("export: '%s' is not a valid identifier\n", 2);
		return (1);
	}
	env_count = 0;
	while (environ[env_count] != NULL)
	{
		existing_var = environ[env_count];
		if (strncmp(existing_var, var, equal_sign - var) == 0
			&& existing_var[equal_sign - var] == '=')
		{
			environ[env_count] = strdup(var);
			return (0);
		}
		env_count++;
	}
	new_environ = malloc((env_count + 2) * sizeof(char *));
	if (!new_environ)
	{
		perror("malloc");
		return (1);
	}
	i = 0;
	while (environ[i] != NULL)
	{
		new_environ[i] = environ[i];
		i++;
	}
	new_environ[i] = strdup(var);
	new_environ[i + 1] = NULL;
	environ = new_environ;
	return (0);
}

void	ft_export(char **args)
{
	int	i;

	i = 1;
	if (!args[1])
	{
		print_env();
		return ;
	}
	while (args[i] != NULL)
	{
		set_env_var(args[i]);
		i++;
	}
}



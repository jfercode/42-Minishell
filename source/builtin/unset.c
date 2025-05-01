/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaferna2 < jaferna2@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 16:42:45 by jaferna2          #+#    #+#             */
/*   Updated: 2025/05/01 18:44:04 by jaferna2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_unset(char **envp, const char *var)
{
	int	i;
	int	j;

	if (!var)
		return (1);
	i = 0;
	j = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var, ft_strlen(var)) == 0
			&& envp[i][ft_strlen(var)] == '=')
		{
			free(envp[i]);
			i++;
			continue ;
		}
		envp[j++] = envp[i++];
	}
	envp[j] = NULL;
	return (0);
}

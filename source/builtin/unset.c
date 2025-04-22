/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penpalac <penpalac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 16:42:45 by penpalac          #+#    #+#             */
/*   Updated: 2025/04/22 16:36:13 by penpalac         ###   ########.fr       */
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
			i++;
			continue ;
		}
		envp[j++] = envp[i++];
	}
	envp[j] = NULL;
	return (0);
}

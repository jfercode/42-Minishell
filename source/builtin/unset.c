/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penpalac <penpalac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 16:42:45 by penpalac          #+#    #+#             */
/*   Updated: 2025/04/11 18:58:49 by penpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_unset(char **envp, const char *var)
{
	int	i;
	int	j;

	if (!var || !getenv(var))
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

// int main() {
//     printf("Antes de unset: %s\n", getenv("TEST_ENV"));

//     my_unset("TEST_ENV");

//     printf("Después de unset: %s\n", getenv("TEST_ENV"));

//     return (0);
// }
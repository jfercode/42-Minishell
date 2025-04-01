/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabalons <pabalons@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 14:52:30 by pabalons          #+#    #+#             */
/*   Updated: 2025/04/01 14:52:31 by pabalons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern char	**environ;

void	ft_unset(const char *var)
{
	int	i;
	int	j;

	if (!var || !getenv(var))
		return ;
	i = 0;
	j = 0;
	while (environ[i])
	{
		if (ft_strncmp(environ[i], var, ft_strlen(var)) == 0
			&& environ[i][ft_strlen(var)] == '=')
		{
			i++;
			continue ;
		}
		environ[j++] = environ[i++];
	}
	environ[j] = NULL;
}

// int main() {
//     printf("Antes de unset: %s\n", getenv("TEST_ENV"));

//     my_unset("TEST_ENV");

//     printf("Después de unset: %s\n", getenv("TEST_ENV"));

//     return (0);
// }
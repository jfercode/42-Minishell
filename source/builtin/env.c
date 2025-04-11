/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penpalac <penpalac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 16:42:36 by penpalac          #+#    #+#             */
/*   Updated: 2025/04/11 18:58:29 by penpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_env(t_ast *node)
{
	int	i;

	i = 0;
	while (node->data->envp[i])
	{
		printf("%s\n", node->data->envp[i]);
		i++;
	}
	return (0);
}

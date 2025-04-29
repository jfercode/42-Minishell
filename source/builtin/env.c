/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaferna2 <jaferna2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 16:42:36 by jaferna2          #+#    #+#             */
/*   Updated: 2025/04/29 17:25:26 by jaferna2         ###   ########.fr       */
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

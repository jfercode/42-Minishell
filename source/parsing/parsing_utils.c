/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabalons <pabalons@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 12:52:40 by pabalons          #+#    #+#             */
/*   Updated: 2025/05/01 15:53:52 by pabalons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*process_exit_value(int exit, char *line, int *index)
{
	char	*tmp2;
	char	*tmp1;
	char	*new_tmp;

	tmp2 = ft_calloc(1, 1);
	while (line[*index] == '$' && line[*index + 1] == '?')
	{
		tmp1 = ft_itoa(exit);
		new_tmp = ft_strjoin(tmp2, tmp1);
		free(tmp2);
		free(tmp1);
		tmp2 = new_tmp;
		*index += 2;
	}
	return (tmp2);
}

int	check_ch(char c)
{
	if (c == '\'')
		return (-1);
	return (0);
}

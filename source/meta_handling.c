/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meta_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penpalac <penpalac@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:36:48 by penpalac          #+#    #+#             */
/*   Updated: 2025/03/20 18:09:09 by penpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_special(char *str, int index)
{
	if (str[index] == '|' || str[index] == '>' || str[index] == '<')
	{
		if (str[index + 1] == str[index])
			return (2);
		if (str[index - 1] == str[index])
			return (2);
		return (1);
	}
	return (0);
}

char	**maker_loop(char **matrix, char **new_mx, int i, int *k)
{
	int	j;
	int	num_tk;

	j = 0;
	while (matrix[i][j])
	{
		num_tk = is_special(matrix[i], j);
		if (num_tk)
		{
			if (j > 0)
				new_mx[(*k)++] = ft_substr(matrix[i], 0, j);
			if (num_tk == 2)
			{
				new_mx[(*k)++] = ft_substr(matrix[i], j, 2);
				j++;
			}
			else
				new_mx[(*k)++] = ft_substr(matrix[i], j, 1);
			matrix[i] += j + 1;
			j = -1;
		}
		j++;
	}
	return (new_mx);
}

char	**nm_maker(char **matrix, char **new_mx, int i, int k)
{
	while (matrix[i])
	{
		new_mx = maker_loop(matrix, new_mx, i, &k);
		if (*matrix[i])
			new_mx[k++] = ft_strdup(matrix[i]);
		i++;
	}
	new_mx[k] = NULL;
	return (new_mx);
}

char	**handle_meta(char **matrix)
{
	char	**new_matrix;
	int		cont;
	int		i;

	i = 0;
	cont = 0;
	while (matrix[i])
	{
		if (is_special(matrix[i], 0) || is_special(matrix[i],
				ft_strlen(matrix[i]) - 1))
			cont += 2;
		else
			cont++;
		i++;
	}
	new_matrix = malloc((cont + 1) * sizeof(char *));
	if (!new_matrix)
		return (NULL);
	new_matrix = nm_maker(matrix, new_matrix, 0, 0);
	return (new_matrix);
}

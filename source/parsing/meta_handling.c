/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meta_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaferna2 <jaferna2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:36:48 by penpalac          #+#    #+#             */
/*   Updated: 2025/03/17 19:06:56 by jaferna2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

char	**nm_maker(char **matrix, char **new_mx, int i, int k)
{
	int	n;

	while (matrix[i])
	{
		n = is_special(matrix[i], 0);
		if (n)
		{
			new_mx[k++] = ft_substr(matrix[i], 0, n);
			if (ft_strlen(matrix[i]) > 2)
				new_mx[k++] = ft_substr(matrix[i], n, ft_strlen(matrix[i]) - n);
		}
		else
		{
			n = is_special(matrix[i], ft_strlen(matrix[i]) - 1);
			if (n)
			{
				new_mx[k++] = ft_substr(matrix[i], 0, ft_strlen(matrix[i]) - n);
				new_mx[k++] = ft_substr(matrix[i], ft_strlen(matrix[i]) - n, n);
			}
			else
				new_mx[k++] = ft_strdup(matrix[i]);
		}
		i++;
	}
	return (new_mx[k] = NULL, new_mx);
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

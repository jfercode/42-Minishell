/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaferna2 < jaferna2@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 18:15:13 by jaferna2          #+#    #+#             */
/*   Updated: 2025/05/01 19:36:42 by jaferna2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	omit_spaces(char *line, int *i)
{
	while (line[*i] == ' ' && line[*i])
		(*i)++;
}

void	free_matrix(char **matrix)
{
	int	i;

	if (!matrix)
		return ;
	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
	matrix = NULL;
}

void	print_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		printf(GREEN"matrix[%d]:"RST" %s\n", i, matrix[i]);
		i++;
	}
}

char	**cleanup_matrix(char **matrix)
{
	int	i;
	int	j;
	int	k;
	int	quotes;

	i = 0;
	quotes = 0;
	while (matrix[i])
	{
		j = 0;
		k = 0;
		while (matrix[i][j])
		{
			if (matrix[i][j] == '\'' || matrix[i][j] == '"')
				quotes = !quotes;
			else
				matrix[i][k++] = matrix[i][j];
			j++;
		}
		matrix[i][k] = '\0';
		i++;
	}
	return (matrix);
}

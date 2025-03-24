/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penpalac <penpalac@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 16:31:34 by penpalac          #+#    #+#             */
/*   Updated: 2025/03/24 16:54:34 by penpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
	$a = 1 -- if $a -- if 1

	echo hola"mundo" - holamundo
	echo $PWD'$PWD'  - ruta$PWD
	echo $PWD"$PWD"  - rutaruta

*/

char	**expand_matrix(char **matrix)
{
	// if no $ -> cleanup
	// if $ -> check comillas and expand or clean

	// check $
	int i;
	int j;
	int ch_env;
	int	ch_simple;
	int	ch_double;

	i = 0;
	ch_env = 0;
	ch_simple = 0;
	ch_double = 0;
	while (matrix[i])
	{
		j = 0;
		while (matrix[i][j])
		{
			if (matrix[i][j] == '$')
				ch_env = 1;
			if (matrix[i][j] == '\'')
				ch_simple = 1;
			if (matrix[i][j] == '\"')
				ch_double = 1;
			j++;
		}
		i++;
	}
	
	if (ch_env == 0)
		matrix = cleanup_matrix(matrix);
	else
	{
		if ((!ch_simple && !ch_double) || (!ch_simple && ch_double))
			matrix = normal_expand(matrix);
		if (ch_simple && !ch_double)
			matrix = nointer_expand(matrix);
		if (ch_simple && ch_double)
			matrix = fuckoff_expand(matrix);
	}
}

//sustituye directamente
char	**normal_expand(char **matrix)
{
	
}

char	**cleanup_matrix(char **matrix)
{
	int	i;
	int	j;

	i = 0;
	while (matrix[i])
	{
		j = 0;
		while (matrix[i][j])
		{
			if (matrix[i][j] == '"' || matrix[i][j] == '\'')
			{
				j++;
				while (matrix[i][j] != '"' && matrix[i][j] != '\'')
				{
					matrix[i][j - 1] = matrix[i][j];
					j++;
				}
				matrix[i][j - 1] = '\0';
			}
			j++;
		}
		i++;
	}
	return (matrix);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penpalac <penpalac@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 18:38:36 by penpalac          #+#    #+#             */
/*   Updated: 2025/03/06 16:02:49 by penpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
char	**create_matrix(char *line)
		analyze the line and create the malloc
char	**handle_quotes(char *line, char **matrix)
		from te line given it creates a matrix where words in quotes get put in the same spot
char	**handle_meta(char **matrix)
		if a matrix spot has a pipe or redirection at the start and it is not just one spot (i.e |cmd),
			it separates them
*/

int	omit_spaces(char *line, int i)
{
	while (line[i] == ' ')
		i++;
	return (i);
}

char	**create_matrix(char *line)
{
	unsigned int	count;
	char			**matrix;
	int				i;

	i = 0;
	count = 0;
	while (line[i])
	{
		while (line[i] == ' ')
			i++;
		if (line[i])
			count++;
		while (line[i] && line[i] != ' ')
			i++;
		i++;
	}
	matrix = malloc((count + 1) * sizeof(char *));
	if (!matrix)
		printf("malloc error\n");
	matrix = split_line(matrix, line);
	matrix = handle_meta(matrix);
	return (matrix);
}

char	**split_line(char **matrix, char *line)
{
	char			quote;
	int				start;
	unsigned int	count;
	int				i;

	i = 0;
	count = 0;
	while (line[i])
	{
		i = omit_spaces(line, i);
		if (line[i] == '"' || line[i] == '\'')
			quote = line[i];
		else
			quote = 0;
		start = i++;
		if (quote)
		{
			while (line[i] != quote && line[i])
				i++;
			matrix[count] = ft_substr(line, start + 1, i - (start + 1));
		}
		else
		{
			while (line[i] != ' ' && line[i])
				i++;
			matrix[count] = ft_substr(line, start, i - start);
		}
		if (quote && line[i] == quote)
			i++;
		matrix[count][i - start] = '\0';
		count++;
		i = omit_spaces(line, i);
	}
	matrix[count] = NULL;
	return (matrix);
}

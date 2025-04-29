/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_creation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaferna2 <jaferna2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 18:16:29 by jaferna2          #+#    #+#             */
/*   Updated: 2025/04/29 18:19:24 by jaferna2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static unsigned int	count_words_in_line(char *line)
{
	int				i;
	unsigned int	count;

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
		if (line[i] != '\0')
			i++;
	}
	return (count);
}

static char	**init_matrix_from_line(char *line, unsigned int count)
{
	char	**matrix;
	char	**tmp;

	matrix = malloc((count + 1) * sizeof(char *));
	if (!matrix)
		return (ft_error("Error: failed matrix creation\n"), NULL);
	tmp = split_line(matrix, line);
	if (!tmp)
	{
		free_matrix(matrix);
		return (NULL);
	}
	if (tmp != matrix)
		free_matrix(matrix);
	return (tmp);
}

static char	**expand_and_clean_matrix(char **matrix, t_data *data)
{
	char	**tmp;

	tmp = expand_matrix(matrix, data);
	if (!tmp)
	{
		free_matrix(matrix);
		return (NULL);
	}
	if (tmp != matrix)
		free_matrix(matrix);
	return (tmp);
}

char	**create_matrix(char *line, t_data *data)
{
	unsigned int	count;
	char			**matrix;

	count = count_words_in_line(line);
	if (!count)
		return (NULL);
	matrix = init_matrix_from_line(line, count);
	if (!matrix)
		return (NULL);
	matrix = expand_and_clean_matrix(matrix, data);
	return (matrix);
}

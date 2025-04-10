/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penpalac <penpalac@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 18:38:36 by penpalac          #+#    #+#             */
/*   Updated: 2025/04/10 11:06:39 by penpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**create_matrix(char *line, t_data *data)
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
		if (line[i] != '\0')
			i++;
	}
	if (!count)
		return (NULL);
	matrix = malloc((count + 1) * sizeof(char *));
	if (!matrix)
		return(ft_error("Error: failed matrix creation\n"), NULL);
	matrix = split_line(matrix, line);
	matrix = expand_matrix(matrix, data);
	return (matrix);
}

char	*get_token(char *line, int *i, char quote)
{
	char	*token;
	int		start;

	start = *i;
	if (quote)
	{
		(*i)++;
		while (line[*i] != quote && line[*i])
			(*i)++;
		token = ft_substr(line, start, (*i + 1) - start);
		if (!token)
			return (free(line), NULL);
		if (line[*i] == quote)
			(*i)++;
	}
	else
	{
		while (line[*i] != ' ' && line[*i])
			(*i)++;
		token = ft_substr(line, start, *i - start);
		if (!token)
			return (free(line), NULL);
	}
	return (token);
}

void	omit_spaces(char *line, int *i)
{
	while (line[*i] == ' ')
			(*i)++;
}

char	**split_line(char **matrix, char *line)
{
	char			quote;
	unsigned int	count;
	int				i;

	i = 0;
	count = 0;
	while (line[i])
	{
		omit_spaces(line, &i);
		if (line[i] == '"' || line[i] == '\'')
			quote = line[i];
		else
			quote = 0;
		matrix[count] = get_token(line, &i, quote);
		if (!matrix[count])
		{
			free_matrix(matrix);
			free(line);
			return (NULL);
		}
		count++;
		omit_spaces(line, &i);
	}
	matrix[count] = NULL;
	return (handle_meta(matrix));
}

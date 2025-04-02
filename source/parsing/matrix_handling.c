/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penpalac <penpalac@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 18:38:36 by penpalac          #+#    #+#             */
/*   Updated: 2025/04/02 19:35:56 by penpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
		if (line[i] != '\0')
			i++;
	}
	matrix = malloc((count + 1) * sizeof(char *));
	if (!matrix)
		return(ft_error("Error: failed matrix creation\n"), NULL);
	split_line(matrix, line);
	matrix = handle_meta(matrix);
	clean_up_matrix(matrix);
	return (matrix);
}

//esto lo limpia, pero en el caso de env entre comillas simples luego no 
//deberái interpretarlo, no sé como hacer eso
void	clean_up_matrix(char **matrix)
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
		token = ft_substr(line, start + 1, *i - (start + 1));
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

void	split_line(char **matrix, char *line)
{
	char			quote;
	unsigned int	count;
	int				i;

	i = 0;
	count = 0;
	while (line[i])
	{
		while (line[i] == ' ')
			i++;
		if (line[i] == '"' || line[i] == '\'')
			quote = line[i];
		else
			quote = 0;
		matrix[count] = get_token(line, &i, quote);
		if (!matrix[count])
		{
			free_matrix(matrix);
			free(line);
			return ;
		}
		count++;
		while (line[i] == ' ')
			i++;
	}
	matrix[count] = NULL;
}

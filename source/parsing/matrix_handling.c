/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penpalac <penpalac@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 18:38:36 by penpalac          #+#    #+#             */
/*   Updated: 2025/03/20 18:11:35 by penpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**clean_up_matrix(char **matrix);

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
		ft_error("Error: failed matrix creation\n");
	ft_printf(STDOUT_FILENO, BLUE"/*****Split_line*****/\n"RST);
	matrix = split_line(matrix, line);
	print_matrix(matrix);
	ft_printf(STDOUT_FILENO, BLUE"/*****Handle_meta*****/\n"RST);
	matrix = handle_meta(matrix);
	matrix = clean_up_matrix(matrix);
	return (matrix);
}

//esto lo limpia, pero en el caso de env entre comillas simples luego no 
//deberái interpretarlo, no sé como hacer eso
char	**clean_up_matrix(char **matrix)
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
		if (line[*i] == quote)
			(*i)++;
	}
	else
	{
		while (line[*i] != ' ' && line[*i])
			(*i)++;
		token = ft_substr(line, start, *i - start);
	}
	return (token);
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
		while (line[i] == ' ')
			i++;
		if (line[i] == '"' || line[i] == '\'')
			quote = line[i];
		else
			quote = 0;
		matrix[count] = get_token(line, &i, quote);
		count++;
		while (line[i] == ' ')
			i++;
	}
	matrix[count] = NULL;
	return (matrix);
}

void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
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

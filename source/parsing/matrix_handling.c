/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaferna2 <jaferna2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 18:38:36 by penpalac          #+#    #+#             */
/*   Updated: 2025/03/17 18:49:18 by jaferna2         ###   ########.fr       */
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
	return (matrix);
}

char	*get_token(char *line, int *i, char quote)
{
	char	*token;
	int		start;

	start = *i;
	if (quote)
	{
		(*i)++; // Skip the opening quote.
		while (line[*i] != quote && line[*i])
			(*i)++;
		token = ft_substr(line, start + 1, *i - (start + 1));
		if (line[*i] == quote)
			(*i)++; // Skip the closing quote.
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

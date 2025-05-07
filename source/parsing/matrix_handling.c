/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaferna2 < jaferna2@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 18:38:36 by jaferna2          #+#    #+#             */
/*   Updated: 2025/05/05 18:53:31 by jaferna2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	support_loop(int *i, char quote, char *line)
{
	(*i)++;
	if (line[*i] == '\0')
		return ;
	while (line[*i] != quote && line[*i])
		(*i)++;
}

static char	*get_quoted_token(char *line, int *i, char quote, int start)
{
	char	*token;

	(*i)++;
	while (line[*i] != quote && line[*i] != '\0')
		(*i)++;
	if (line[*i + 1] == ' ' && line[*i + 1] != '\0')
		token = ft_substr(line, start, (*i + 1) - start);
	else
	{
		if (line[*i] == quote)
			(*i)++;
		while (line[*i] && line[*i] != ' ')
			support_loop(i, quote, line);
		token = ft_substr(line, start, (*i + 1) - start);
	}
	if (!token)
		return (free(line), NULL);
	if (line[*i] == quote && line[*i])
		(*i)++;
	return (token);
}

char	*get_token(char *line, int *i, char quote)
{
	char	*token;
	int		start;

	start = *i;
	if (quote)
		token = get_quoted_token(line, i, quote, start);
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
	return (separate_tokens(matrix));
}

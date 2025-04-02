/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penpalac <penpalac@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 18:38:36 by penpalac          #+#    #+#             */
/*   Updated: 2025/04/02 20:02:19 by penpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**create_matrix(char *line, char **envp)
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
	matrix = expand_matrix(matrix, envp);
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

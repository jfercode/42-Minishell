/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penpalac <penpalac@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 18:38:36 by penpalac          #+#    #+#             */
/*   Updated: 2025/02/25 19:28:09 by penpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char    get_quote(char ch)
{
	printf("gets into quote\n");
    char    quote;

    if (ch == '"' || ch == '\'')
        quote = ch;
    else
        quote = 0;
    return (quote);
}

unsigned int count_words(char *line)
{
	printf("gets into count\n");
    unsigned int count;
    int i;

	i = 0;
    while (line[i])
    {
		while (line[i] == ' ')
			i++;
		if(line[i])
			count++;
		while (line[i] == ' ' && line[i] != ' ')
			i++;
    }
    return (count);
}

int read_until(char *line, int i, char quote)
{
	printf("gets into read\n");
	if (quote)
		while (line[i] != quote && line[i])
			i++;
	else
		while (line[i] != ' ' && line[i])
			i++;
    return (i);
}

int omit_spaces(char *line, int i)
{
	printf("gets into spaces\n");
    while(line[i] == ' ')
        i++;
    // if (line[i] == '\0')
    //     perror("No line found"); //call error
    return (i);
}

char	**create_matrix(char *line)
{
	unsigned int	count;
	char			**matrix;
	char			quote;
	int				i;
	int				start;
	int				word_i;

	count = count_words(line);
	matrix = malloc((count + 1) * sizeof(char *));
	i = 0;
	word_i = 0;
	while(line[i])
	{
		i = omit_spaces(line, i);
		if (!line[i])
			break;
		quote = get_quote(line[i]);
		start = i;
		i = read_until(line, i, quote);
		matrix[word_i++] = ft_substr(line + start, start, i - start);
		i = omit_spaces(line, i);
		i++;	
	}
	matrix[word_i] = NULL;
	return (matrix);
}

char	**handle_meta(char **matrix)
{
	char	**new_matrix;
	int		new;
	int		i;
	int		j;

	i = 0;
	new = 0;
	
	 while (matrix[i])
	 {
    	if ((matrix[i][0] == '|' || matrix[i][0] == '<' || matrix[i][0] == '>') && strlen(matrix[i]) > 1)
		{
            new_matrix[new++] = strndup(matrix[i], 1);
            new_matrix[new++] = strdup(matrix[i] + 1);
        } 
		else
		{
            new_matrix[new++] = strdup(matrix[i]);
        }
        i++;
    }
    new_matrix[new] = NULL;
    return (new_matrix);
}

char	**split_line(char *line)
{
	char	            **matrix;
	char	            quote;
	int		            start;
	unsigned int		count;
	int		            i;

	count = count_words(line);
	i = 0;
	matrix = malloc(count + sizeof(char)); // needs a better way to count
    count = 0;
	while (line[i])
	{
        i = omit_spaces(line, i);
		quote = get_quote(line[i]);
		start = i++;
        i = read_until(line, i, quote);
		matrix[count] = ft_substr(line, start, i - start);
		if (quote && line[i] == quote)
			i++;
		matrix[count][i - start] = '\0';
		count++;
		i = omit_spaces(line, i);
	}
	matrix[count] = NULL;
	return (matrix);
}

char	**split_meta(char **matrix)
{
	char	tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while(matrix[j])
		j++;
	while (matrix[i])
	{
		if (matrix[i][0] == '|' || matrix[i][0] == '<')
		{
			tmp = matrix[i][0];
			while(j > i + 1)
			{
				matrix[j + 1] = matrix[j];
				j--;
			}
			matrix[j] = tmp;
		}
		i++;
	}
}

/*
char	**create_matrix(char *line)
		analyze the line and create the malloc
char	**handle_quotes(char *line, char **matrix)
		from te line given it creates a matrix where words in quotes get put in the same spot
char	**handle_meta(char **matrix)
		if a matrix spot has a pipe or redirection at the start and it is not just one spot (i.e |cmd), it separates them
*/
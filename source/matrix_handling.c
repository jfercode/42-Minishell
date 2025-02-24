/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penpalac <penpalac@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 18:38:36 by penpalac          #+#    #+#             */
/*   Updated: 2025/02/24 18:40:20 by penpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char    get_quote(char ch)
{
    char    quote;

    if (ch == '"' || ch == '\'')
        quote = ch;
    else
        quote = 0;
    return (quote);
}

unsigned int count_words(char *line)
{
    unsigned int count;
    int i;

    while (line[i])
    {
        i++;
    }
    return (count);
}

int read_until(char *line, int i, char quote)
{
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
    while(line[i] == ' ')
        i++;
    if (line[i] == '\0')
        return (0); //call error
    return (i);
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
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meta_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penpalac <penpalac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:36:48 by penpalac          #+#    #+#             */
/*   Updated: 2025/04/21 17:05:35 by penpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	is_quoted_token(char *token)
{
	int	len;

	len = ft_strlen(token);
	return ((token[0] == '\'' && token[len - 1] == '\'') || (token[0] == '"'
			&& token[len - 1] == '"'));
}

int	is_special(char *str, int index)
{
	if (str[index] == '|' || str[index] == '>' || str[index] == '<')
	{
		if (str[index + 1] == str[index])
			return (2);
		if (str[index - 1] == str[index])
			return (2);
		return (1);
	}
	return (0);
}

static void	append_substr(char **dest, char *src, int start, int len, int *k)
{
	dest[(*k)++] = ft_substr(src, start, len);
}

static int	handle_special_token(char **dest, char *line, int j, int *k)
{
	int	n;

	n = is_special(line, j);
	if (n == 2)
		append_substr(dest, line, j, 2, k);
	else
		append_substr(dest, line, j, 1, k);
	return (j + n);
}

static void	split_special_tokens(char **matrix, char **new_mx, int *k, int i)
{
	int	start;
	int	j;
	int	n;

	start = 0;
	j = 0;
	while (matrix[i][j])
	{
		n = is_special(matrix[i], j);
		if (n)
		{
			if (j > start)
				append_substr(new_mx, matrix[i], start, j - start, k);
			j = handle_special_token(new_mx, matrix[i], j, k);
			start = j;
		}
		else
			j++;
	}
	if (j > start)
		append_substr(new_mx, matrix[i], start, j - start, k);
}

char	**nm_maker(char **matrix, char **new_mx, int i, int k)
{
	while (matrix[i])
	{
		if (!is_quoted_token(matrix[i]))
			split_special_tokens(matrix, new_mx, &k, i);
		else
			new_mx[k++] = ft_strdup(matrix[i]);
		i++;
	}
	new_mx[k] = NULL;
	return (new_mx);
}

char	**separate_tokens(char **matrix)
{
	char	**new_matrix;
	int		cont;
	int		i;

	i = 0;
	cont = 0;
	while (matrix[i])
	{
		if (!is_quoted_token(matrix[i]) && (is_special(matrix[i], 0)
				|| is_special(matrix[i], ft_strlen(matrix[i]) - 1)))
			cont += 2;
		else
			cont++;
		i++;
	}
	new_matrix = malloc((cont + 1) * sizeof(char *));
	if (!new_matrix)
		return (NULL);
	new_matrix = nm_maker(matrix, new_matrix, 0, 0);
	return (new_matrix);
}

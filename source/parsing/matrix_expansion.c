/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaferna2 < jaferna2@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 16:31:34 by penpalac          #+#    #+#             */
/*   Updated: 2025/04/21 18:19:49 by jaferna2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_envp(char **envp, char *var)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(var);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var, len) == 0 && envp[i][len] == '=')
			return (envp[i] + len + 1);
		i++;
	}
	return (NULL);
}

char	**expansion(char **matrix, char **envp, int *i, int *j)
{
	char	*tmp;
	char	*var;
	char	*new;
	char	*prefix;
	int		start;

	start = ++(*j);
	while (matrix[*i][(*j)] && (ft_isalnum(matrix[*i][(*j)]) || \
		matrix[*i][(*j)] == '_'))
		(*j)++;
	tmp = ft_substr(matrix[*i], start, *j - start);
	var = get_envp(envp, tmp);
	free(tmp);
	if (var)
	{
		prefix = ft_substr(matrix[*i], 0, start - 1);
		new = ft_strjoin(prefix, var);
		new = ft_strjoin(new, &matrix[*i][*j]);
		if (new)
		{
			free(matrix[*i]);
			matrix[*i] = new;
		}
	}
	return (matrix);
}

char	**cleanup_matrix(char **matrix)
{
	int	i;
	int	j;
	int	k;
	int	quotes;

	i = 0;
	quotes = 0;
	while (matrix[i])
	{
		j = 0;
		k = 0;
		while (matrix[i][j])
		{
			if (matrix[i][j] == '\'' || matrix[i][j] == '"')
				quotes = !quotes;
			else
				matrix[i][k++] = matrix[i][j];
			j++;
		}
		matrix[i][k] = '\0';
		i++;
	}
	return (matrix);
}

char	**expand_matrix(char **matrix, t_data *data)
{
	int	i;
	int	j;
	int	ch_single;

	i = 0;
	while (matrix[i])
	{
		j = 0;
		ch_single = 0;
		while (matrix[i][j])
		{
			if (matrix[i][j] == '\'')
				ch_single = !ch_single;
			else if (matrix[i][j] == '$' && matrix[i][j + 1] == '?')
				matrix[i] = ft_itoa(data->exit_status);
			else if (matrix[i][j] == '$' && !ch_single)
				matrix = expansion(matrix, data->envp, &i, &j);
			j++;
		}
		i++;
	}
	matrix = cleanup_matrix(matrix);
	return (matrix);
}

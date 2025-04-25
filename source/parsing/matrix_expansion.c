/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penpalac <penpalac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 16:31:34 by penpalac          #+#    #+#             */
/*   Updated: 2025/04/25 17:32:57 by penpalac         ###   ########.fr       */
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

static char	*exit_value(int exit, char *line, int start)
{
	char	*tmp1;
	char	*tmp2;
	int		i;
	int		j;

	i = start;
	tmp2 = ft_calloc(1, 1);
	while (line[i] == '$' && line[i + 1] == '?')
	{
		tmp1 = ft_itoa(exit);
		tmp2 = ft_strjoin(tmp2, tmp1);
		free(tmp1);
		i += 2;
	}
	if (line[i])
	{
		tmp1 = malloc(ft_strlen(line) - ft_strlen(tmp2) + 1);
		j = 0;
		while (line[i] != '\0' && line[i] != ' ')
			tmp1[j++] = line[i++];
		tmp2 = ft_strjoin(tmp2, tmp1);
		free(tmp1);
	}
	return (tmp2);
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
				matrix[i] = exit_value(data->exit_status, matrix[i], j);
			else if (matrix[i][j] == '$' && !ch_single)
				matrix = expansion(matrix, data->envp, &i, &j);
			j++;
		}
		i++;
	}
	matrix = cleanup_matrix(matrix);
	return (matrix);
}

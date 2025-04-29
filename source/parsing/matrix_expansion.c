/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaferna2 <jaferna2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 16:31:34 by jaferna2          #+#    #+#             */
/*   Updated: 2025/04/29 18:12:57 by jaferna2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*get_envp(char **envp, char *var)
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

static char	*get_envp_ext(char *str, int start, int *end, char **envp)
{
	char	*var;
	char	*val;
	int		j;

	j = start;
	while (str[j] && (ft_isalnum(str[j]) || str[j] == '_'))
		j++;
	var = ft_substr(str, start, j - start);
	if (!var)
		return (NULL);
	val = get_envp(envp, var);
	free(var);
	if (!val)
		return (NULL);
	*end = j;
	return (val);
}

char	**expansion(char **matrix, char **envp, int *i, int *j)
{
	char	*prefix;
	char	*joined;
	char	*val;
	char	*new;
	int		start;

	start = ++(*j);
	val = get_envp_ext(matrix[*i], start, j, envp);
	if (!val)
		return (matrix);
	prefix = ft_substr(matrix[*i], 0, start - 1);
	if (!prefix)
		return (matrix);
	joined = ft_strjoin(prefix, val);
	free(prefix);
	if (!joined)
		return (matrix);
	new = ft_strjoin(joined, &matrix[*i][*j]);
	free(joined);
	if (new)
	{
		free(matrix[*i]);
		matrix[*i] = new;
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
			else if (matrix[i][j] == '$' && matrix[i][j + 1]
				&& matrix[i][j + 1] == '?')
				matrix[i] = exit_value(data->exit_status, matrix[i], j);
			else if (matrix[i][j] == '$' && !ch_single && matrix[i][j + 1])
				matrix = expansion(matrix, data->envp, &i, &j);
			j++;
		}
		i++;
	}
	matrix = cleanup_matrix(matrix);
	return (matrix);
}

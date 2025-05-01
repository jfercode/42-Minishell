/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabalons <pabalons@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 16:31:34 by jaferna2          #+#    #+#             */
/*   Updated: 2025/05/01 15:52:49 by pabalons         ###   ########.fr       */
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
	char	*new_tmp;
	int		i;
	int		j;

	i = start;
	tmp2 = process_exit_value(exit, line, &i);
	if (line[i])
	{
		tmp1 = malloc(ft_strlen(line + i + 1));
		if (!tmp1)
			return (free(tmp2), NULL);
		j = 0;
		while (line[i] != '\0' && line[i] != ' ')
			tmp1[j++] = line[i++];
		tmp1[j] = '\0';
		new_tmp = ft_strjoin(tmp2, tmp1);
		free(tmp2);
		free(tmp1);
		tmp2 = new_tmp;
	}
	free(line);
	return (tmp2);
}

char	**expand_matrix(char **matrix, t_data *data)
{
	int		i;
	int		j;
	int		ch_single;
	char	*old_line;

	i = 0;
	old_line = matrix[i];
	while (matrix[i])
	{
		j = 0;
		ch_single = 0;
		while (j < ft_strlen(matrix[i]))
		{
			ch_single = check_ch(matrix[i][j]);
			if (matrix[i][j] == '$' && j + 1 < ft_strlen(matrix[i])
				&& matrix[i][j + 1] == '?')
				matrix[i] = exit_value(data->exit_status, old_line, j);
			else if (matrix[i][j] == '$' && !ch_single && j
				+ 1 < ft_strlen(matrix[i]))
				matrix = expansion(matrix, data->envp, &i, &j);
			j++;
		}
		i++;
	}
	return (cleanup_matrix(matrix));
}

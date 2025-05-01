/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabalons <pabalons@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 16:31:34 by jaferna2          #+#    #+#             */
/*   Updated: 2025/05/01 12:23:42 by pabalons         ###   ########.fr       */
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
    char *tmp2 = ft_calloc(1, 1);
    int i = start;

    while (line[i] == '$' && line[i + 1] == '?') {
        char *tmp1 = ft_itoa(exit);
        char *new_tmp = ft_strjoin(tmp2, tmp1);
        free(tmp2);
        free(tmp1);
        tmp2 = new_tmp;
        i += 2;
    }
    if (line[i]) {
        size_t remaining_len = ft_strlen(line + i);
        char *tmp1 = malloc(remaining_len + 1);
        if (!tmp1) {
            free(tmp2);
            return NULL;
        }
        int j = 0;
        while (line[i] != '\0' && line[i] != ' ') {
            tmp1[j++] = line[i++];
        }
        tmp1[j] = '\0';
        char *new_tmp = ft_strjoin(tmp2, tmp1);
        free(tmp2);
        free(tmp1);
        tmp2 = new_tmp;
    }
    return tmp2;
}

char	**expand_matrix(char **matrix, t_data *data)
{
    int i = 0;
    while (matrix[i]) {
        int j = 0;
        int ch_single = 0;
        int len = ft_strlen(matrix[i]);
        while (j < len) {
            if (matrix[i][j] == '\'') {
                ch_single = !ch_single;
            } else if (matrix[i][j] == '$' && j + 1 < len && matrix[i][j + 1] == '?') {
                // Guardar el token original y liberarlo después de reemplazarlo
                char *old_line = matrix[i];
                matrix[i] = exit_value(data->exit_status, old_line, j);
                free(old_line); // Liberar el token original (ej. "$?")
                len = ft_strlen(matrix[i]); // Actualizar longitud
                j = -1; // Reiniciar el análisis desde el inicio del nuevo token
                break; // Salir para reiniciar el loop con el nuevo valor de j
            } else if (matrix[i][j] == '$' && !ch_single && j + 1 < len) {
                matrix = expansion(matrix, data->envp, &i, &j);
                len = ft_strlen(matrix[i]); // Actualizar longitud
                j = -1; // Reiniciar el análisis
                break;
            }
            j++;
        }
        i++;
    }
    return cleanup_matrix(matrix);
}

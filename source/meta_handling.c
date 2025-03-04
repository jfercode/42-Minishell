/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meta_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penpalac <penpalac@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:36:48 by penpalac          #+#    #+#             */
/*   Updated: 2025/03/04 18:35:21 by penpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*putcharstr(char c)
{
	char	*str;

	str = ft_calloc(2, sizeof(char));
	str[0] = c;
	str[1] = '\0';
	return (str);
}

char	*ft_strdupplus(const char *s, int n)
{
	size_t	sl;
	char	*ns;
	int		i;

	sl = ft_strlen(s);
	ns = (char *)malloc((sl + 1) * sizeof(char));
	if (!ns)
		return (NULL);
	i = 0;
	while (s[i])
	{
		ns[i] = s[i + n];
		i++;
	}
	ns[i] = '\0';
	return (ns);
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

char	**handle_meta(char **matrix)
{
	char	**new_matrix;
	int		k;
	int		i;
	int		cont;
	int		n;

	i = 0;
	k = 0;
	cont = 0;
	while (matrix[i])
	{
		if (is_special(matrix[i], 0) || is_special(matrix[i],
				ft_strlen(matrix[i]) - 1))
			cont += 2;
		else
			cont++;
		i++;
	}
	new_matrix = malloc((cont + 1) * sizeof(char *));
	if (!new_matrix)
		return (NULL);
	i = 0;
	while (matrix[i])
	{
		n = is_special(matrix[i], 0);
		if (n)
		{
			new_matrix[k++] = ft_substr(matrix[i], 0, n);
			new_matrix[k++] = ft_substr(matrix[i], n, ft_strlen(matrix[i]) - n);
		}
		else
		{
			n = is_special(matrix[i], ft_strlen(matrix[i]) - 1);
			if (n)
			{
				new_matrix[k++] = ft_substr(matrix[i], 0, ft_strlen(matrix[i]) - n);
				new_matrix[k++] = ft_substr(matrix[i], ft_strlen(matrix[i]) - n, n);
			}
			else
				new_matrix[k++] = ft_strdup(matrix[i]);
		}
		i++;
	}
	new_matrix[k] = NULL;
	return (new_matrix);
}

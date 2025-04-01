/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabalons <pabalons@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 11:28:07 by pabalons          #+#    #+#             */
/*   Updated: 2025/04/01 13:52:16 by pabalons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern char	**environ;

static int	check_arg(int ar, char *str)
{
	return (ft_strncmp("-n", str, ft_strlen(str)));
}

char	*set_var(char *str)
{
	char	c;
	size_t	str_len;
	char	*res;

	if (!str)
		return (NULL);
	c = '=';
	str_len = ft_strlen(str);
	res = malloc(str_len + 1 + 1);
	strcpy(res, str);
	res[str_len] = c;
	res[str_len + 1] = '\0';
	ft_memmove(res, res + 1, ft_strlen(res));
	return (res);
}

static int	check_var(char *str)
{
	if (str[0] == '$')
		return (1);
	return (0);
}

static int	print_var(char *str)
{
	int		i;
	char	*substr;
	int		j;
	int		break_j;

	i = 0;
	j = 0;
	break_j = 0;
	while (environ[i])
	{
		if (strstr(environ[i], str) != NULL)
		{
			while (environ[i][j] != '=')
				j++;
			j++;
			break_j = j;
			while (environ[i][j])
			{
				write(1, &environ[i][j], 1);
				j++;
			}
			write(1, " ", 1);
			return ((j - break_j) + 1);
		}
		i++;
	}
	return (0);
}

int	ft_echo(int ar, char **args)
{
	int		i;
	int		n_line;
	int		bytes_printed;
	char	*var;

	i = 1;
	n_line = 1;
	bytes_printed = 0;
	if (ar > 1 && check_arg(ar, args[i]) == 0)
	{
		n_line = 0;
		i++;
	}
	while (i < ar)
	{
		if (check_var(args[i]) == 1)
		{
			var = set_var(args[i]);
			print_var(var);
			i++;
		}
		printf("%s ", args[i]);
		bytes_printed += (ft_strlen(args[1]) + 1);
		i++;
	}
	if (n_line == 1)
	{
		printf("\n");
		bytes_printed += 1;
	}
	return (bytes_printed);
}

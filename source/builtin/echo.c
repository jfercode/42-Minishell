/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penpalac <penpalac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 11:28:07 by pabalons          #+#    #+#             */
/*   Updated: 2025/04/11 18:56:36 by penpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	check_jump(int ac, char *str)
{
	return (ft_strncmp("-n", str, ft_strlen(str)));
}

int	ft_echo(int ac, char **args)
{
	int		i;
	int		n_line;
	int		bytes_printed;
	char	*var;

	i = 1;
	n_line = 1;
	bytes_printed = 0;
	if (ac > 1 && check_jump(ac, args[i]) == 0)
	{
		n_line = 0;
		i++;
	}
	while (i < ac)
	{
		printf("%s ", args[i]);
		bytes_printed += (ft_strlen(args[1]) + 1);
		i++;
	}
	if (n_line == 1)
	{
		printf("\n");
		bytes_printed += 1;
	}
	return (0);
}

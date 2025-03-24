/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaferna2 <jaferna2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 11:28:07 by pabalons          #+#    #+#             */
/*   Updated: 2025/03/17 18:55:39 by jaferna2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	check_arg(int ar, char *str)
{
	return (ft_strncmp("-n", str, ft_strlen(str)));
}

// Funcion que replica el funcionamiento de echo
// Imprime en pantalla los argumentos que recibe
// Si recibe -n no imprime salto de linea
// Retorna el numero de bytes escritos
int	ft_echo(int ar, char **args)
{
	int	i;
	int	n_line;
	int	bytes_printed;

	i = 1;
	n_line = 1;
	bytes_printed = 0;
	if (ar > 1 && check_arg(ar, args[1]) == 0)
	{
		n_line = 0;
		i++;
	}
	while (i < ar)
	{
		bytes_printed += write(1, args[i], ft_strlen(args[i]));
		if (i < ar - 1)
			bytes_printed += write(1, " ", 1);
		i++;
	}
	if (n_line)
		bytes_printed += write(1, "\n", 1);
	return (bytes_printed);
}

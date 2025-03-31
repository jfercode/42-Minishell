/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabalons <pabalons@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 11:28:07 by pabalons          #+#    #+#             */
/*   Updated: 2025/03/31 15:53:53 by pabalons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern char	**environ;

static int	check_arg(int ar, char *str)
{
	return (ft_strncmp("-n", str, ft_strlen(str)));
}

// Funcion que replica el funcionamiento de echo
// Imprime en pantalla los argumentos que recibe
// Si recibe -n no imprime salto de linea
// Retorna el numero de bytes escritos

static int check_var(char *str)
{
	if(str[0] == '$')
		return 1;
	return 0;
}

static int print_var(char *str)
{
	ft_env();
	return 0;
}


int	ft_echo(int ar, char **args)
{
	int	i;
	int	n_line;
	int	bytes_printed;

	i = 1;
	n_line = 1;
	bytes_printed = 0;


	if (ar > 1 && check_arg(ar, args[i]) == 0)
	{
		n_line = 0;
		i++;
	}

	while(i < ar)
	{
		if(check_var(args[i]) == 1)
		{
			print_var(args[i]);
			printf("Aaaaaaaaaaaa");
			i++;		
		}
		printf("%s ",args[i]);
		bytes_printed += (ft_strlen(args[1]) + 1);
		i++;	
	}
	if(n_line == 1)
	{
		printf("\n");
		bytes_printed += 1;
	}

	return (bytes_printed);
}

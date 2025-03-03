/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabalons <pabalons@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 11:28:07 by pabalons          #+#    #+#             */
/*   Updated: 2025/03/03 11:28:07 by pabalons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int check_arg(int ar,char *str)
{
    return(ft_strncmp("-n", str, ft_strlen(str)));
}



//Function that replicates the usage of the echo utility. On success returns the number of bytes printed
int ft_echo(int ar, char **args)
{
    if (ar == 3)
    {
        if (check_arg(ar,args[0]) != 0)
            return -1;
        else
        {
            ft_putstr_fd(args[1],1);
            return(ft_strlen(args[1]));
        }
    }
    else
    {
        ft_putstr_fd(args[2],1);
        printf("\n");
        return(ft_strlen(args[2]));
    }       
}

    
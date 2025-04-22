/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaferna2 < jaferna2@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 11:03:01 by jaferna2          #+#    #+#             */
/*   Updated: 2025/04/22 17:03:22 by jaferna2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// void	ft_handle_sigint(int sig)
// {
// 	if (sig == SIGINT)
// 	{
// 		if (g_shell_mode == NORMAL)
// 		{
// 						write(STDOUT_FILENO, "PAPAMOVIL2\n", 12);
// 			write(STDOUT_FILENO, "\n", 1);
// 			rl_on_new_line();
// 			rl_replace_line("", 0);
// 			rl_redisplay();
// 		}
// 		else if (g_shell_mode == CMD)
// 		{
// 			write(STDOUT_FILENO, "\n", 1);
// 			return ;
// 		}
// 		else if (g_shell_mode == HEREDOC)
// 		{
// 			// g_shell_mode = NORMAL;
// 			write(STDOUT_FILENO, "\n", 1);
// 			return ;
// 		}
// 	}
// }

void	ft_handle_sigint_normal(int sig)
{
	if (sig == SIGINT)
		
		{
			write(STDOUT_FILENO, "\n", 1);
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
}

void	ft_handle_sigint_bloq(int sig)
{
	if (sig == SIGINT)
	{
		write (STDOUT_FILENO, "\n", 1);
		return ;
	}
}

void	ft_handle_sigint_here(int sig)
{
	if (sig == SIGINT)
	{
		write (STDOUT_FILENO, "\n", 1);
		exit (1);
	}
}

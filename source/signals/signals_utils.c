/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaferna2 < jaferna2@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 11:03:01 by jaferna2          #+#    #+#             */
/*   Updated: 2025/04/09 18:37:54 by jaferna2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		if (g_shell_mode == NORMAL)
		{
			write(STDOUT_FILENO, "\n", 1);
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
		else if (g_shell_mode == CMD)
		{
			write(STDOUT_FILENO, "\n", 1);
			return ;
		}
		else if (g_shell_mode == HEREDOC)
		{
			g_shell_mode = NORMAL;
		}
	}
}

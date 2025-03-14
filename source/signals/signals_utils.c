/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaferna2 <jaferna2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 11:03:01 by jaferna2          #+#    #+#             */
/*   Updated: 2025/03/14 17:04:12 by jaferna2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Sets up a signal handler for SIGUSR1 or SIGUSR2.
 *
 * This function configures a signal handler for SIGUSR1 or SIGUSR2, allowing 
 * the user to specify a custom handler function. 
 * 
 * It also provides an option to use `SA_SIGINFO` 
 * to receive additional information about the signal.
 *
 * @param signo The signal to handle (SIGUSR1 or SIGUSR2).
 * @param handler A function pointer to handle the received signal.
 * @param use_siginfo A boolean flag indicating whether to use `SA_SIGINFO` 
 * for extended signal information.
 */
void	ft_signal(int signo, void *handler, bool use_siginfo)
{
	struct sigaction	sa;

	sa.sa_sigaction = handler;
	sigemptyset(&sa.sa_mask);
	if (sigaction(signo, &sa, NULL) < 0)
		ft_error_exit("Error. sigaction failed\n");
}

void	ft_handle_sigint(int sig)
{
	if (sig != SIGINT)
		ft_printf(STDERR_FILENO, RED"Error: failed SIGINT\n"RST);
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ft_handle_sigterm(int sig)
{
	if (sig != SIGTERM)
		ft_printf(STDERR_FILENO, RED"Error: failed SIGTERM\n"RST);
	if (!isatty(STDIN_FILENO))
		g_running = false;
}

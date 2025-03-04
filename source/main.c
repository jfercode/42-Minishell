/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penpalac <penpalac@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 15:35:43 by jaferna2          #+#    #+#             */
/*   Updated: 2025/03/04 18:38:47 by penpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool		g_running = true;

static void	ft_start_gigachell(void)
{
	ft_signal(SIGINT, ft_handle_sigint, false);
	ft_signal(SIGTERM, ft_handle_sigterm, false);
	ft_signal(SIGQUIT, SIG_IGN, false);
}

// LINE IS GOING TO BE OUR TEXT TO TOKENIZE
int	main(void)
{
	char	*line;

	while (g_running)
	{
		line = readline(GREEN"Gigachell> "RST);
		if (!line)
		{
			printf("Leaving Gigachell...\n");
			break;
		}
		else if (*line)
			add_history(line);
		free (line);	
	}
	rl_clear_history();
	return (0);
}

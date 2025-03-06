/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penpalac <penpalac@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 15:35:43 by jaferna2          #+#    #+#             */
/*   Updated: 2025/03/06 16:00:39 by penpalac         ###   ########.fr       */
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
			break;
		else if (*line)
		{
			add_history(line);
			syntax_error(line);
			char	**mtx = create_matrix(line);
			for (int i = 0; mtx[i]; i++)
				printf("matrix[%d]: %s\n", i, mtx[i]);
			t_ast *ast = create_ast(mtx);
			if(!ast)
				// ERROR
			print_ast(ast, 0);
		}	
		free (line);	
	}
	printf("Leaving Gigachell...\n");
	rl_clear_history();
	return (EXIT_SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaferna2 <jaferna2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 15:35:43 by jaferna2          #+#    #+#             */
/*   Updated: 2025/03/14 18:19:28 by jaferna2         ###   ########.fr       */
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

static void	ft_exec_line(char *line)
{
	char	**mtx;

	add_history(line);
	if (syntax_error(line) == ERROR)
		free(line);
	else
	{
		mtx = create_matrix(line);
		print_matrix(mtx);
		t_ast *ast = create_ast(mtx);
		if(!ast)
			ft_error_exit("Error creating AST\n");
		print_ast(ast, 0); // TO DO -> DELETE PRINT_AST -> EXECUTE AST HERE
		free_ast(ast);
		free_matrix(mtx);
	}
}
 
// LINE IS GOING TO BE OUR TEXT TO TOKENIZE
int	main(void)
{
	char	*line;

	ft_start_gigachell();
	while (g_running)
	{
		line = readline(GREEN"Gigachell> "RST);
		if (!line)
			break;
		else if (*line)
			ft_exec_line(line);
		free (line);
	}
	printf("Leaving Gigachell...\n");
	rl_clear_history();
	return (EXIT_SUCCESS);
}

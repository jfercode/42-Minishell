/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaferna2 <jaferna2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/03/26 17:14:54 by jaferna2         ###   ########.fr       */
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

static void	ft_exec_line(char *line, char **envp)
{
	char	**mtx;
	t_ast 	*ast;

	add_history(line);
	if (syntax_error(line) == ERROR)
	{
		perror("syntax");
		free(line);
		return;
	}
	else
	{
		mtx = create_matrix(line);
		ast = create_ast(mtx, envp);
		if(!ast)
			ft_error_exit("Error creating AST\n");
		print_ast(ast, 0);
		free_ast(ast);
		free_matrix(mtx);
	}
}

/**
 * Main function of the program
 */
int	main(int argc, char **argv, char **envp)
{
	char	*line;
	char	**mtx;
	t_ast	*ast;

	ft_start_gigachell();
	(void) argc;
	(void) argv;
	while (g_running)
	{
		line = readline(GREEN "Gigachell> " RST);
		if (!line)
			break ;
		else if (*line)
			ft_exec_line(line, envp);
	}
	printf("Leaving Gigachell...\n");
	rl_clear_history();
	return (EXIT_SUCCESS);
}

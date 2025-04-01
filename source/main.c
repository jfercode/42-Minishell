/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaferna2 <jaferna2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 10:16:57 by jaferna2          #+#    #+#             */
/*   Updated: 2025/03/31 19:48:43 by jaferna2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	ft_start_gigachell(void)
{
	signal(SIGINT, ft_handle_sigint);
	signal(SIGTERM, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

static void	ft_exec_line(char *line, char **envp)
{
	char	**mtx;
	t_ast	*ast;

	add_history(line);
	if (syntax_error(line) == ERROR)
	{
		ft_error("Syntax error");
		free(line);
		return ;
	}
	else
	{
		mtx = create_matrix(line);
		ast = create_ast(mtx, envp);
		if (!ast)
			ft_error_exit("Error creating AST\n");
		execute_ast(ast);
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

	(void) argc;
	(void) argv;
	while (1)
	{
		ft_start_gigachell();
		line = readline(GREEN "Gigachell> " RST);
		if (!line)
		{
			ft_printf(STDOUT_FILENO, "Leaving Gigachell...\n");
			break ;
		}
		else if (*line)
			ft_exec_line(line, envp);
		free(line);
	}
	rl_clear_history();
	return (EXIT_SUCCESS);
}

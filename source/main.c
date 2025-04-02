/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penpalac <penpalac@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/04/02 19:33:41 by penpalac         ###   ########.fr       */
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
		return ;
	else
	{
		mtx = create_matrix(line);
		if (!mtx)
			ft_error_exit("Error creating matrix\n");
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penpalac <penpalac@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 15:23:07 by penpalac          #+#    #+#             */
/*   Updated: 2025/03/26 15:23:51 by penpalac         ###   ########.fr       */
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
	t_ast	*ast;

	add_history(line);
	if (syntax_error(line) == ERROR)
	{
		perror("syntax");
		free(line);
		return ;
	}
	else
	{
		mtx = create_matrix(line, envp);
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

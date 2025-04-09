/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaferna2 < jaferna2@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/04/09 18:44:33 by jaferna2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_shell_mode = 0;

static void	ft_start_gigachell(void)
{
	struct sigaction sa;

	g_shell_mode = NORMAL;
	signal(SIGINT, ft_handle_sigint);
	signal(SIGTERM, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = ft_handle_sigint;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		ft_error("Failed sigaction");
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
		mtx = create_matrix(line, envp);
		if (!mtx && mtx == NULL)
		{
			ft_error("Error creating matrix\n");
			return ;
		}
		ast = create_ast(mtx, envp);
		if (!ast)
		{
			ft_error("Error creating AST\n");
			return ;
		}
		execute_ast(ast);
		free_ast(ast);
		free_matrix(mtx);
	}
}

static char	*prompt_readline(void)
{
	char	*temp;
	char	*path;
	char	*prompt;

	path = ft_strjoin(GREEN, getcwd(NULL, 0));
	temp = ft_strjoin(path, "/");
	prompt = ft_strjoin(temp, "Gigachell> " RST);
	free(path);
	free(temp);
	return (prompt);
}

/**
 * Main function of the program
 */
int	main(int argc, char **argv, char **envp)
{
	char	*line;
	char	**mtx;
	t_ast	*ast;

	(void)argc;
	(void)argv;
	while (1)
	{
		ft_start_gigachell();
		line = readline(prompt_readline());
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

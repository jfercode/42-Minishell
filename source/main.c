/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabalons <pabalons@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 18:07:39 by pabalons          #+#    #+#             */
/*   Updated: 2025/04/09 18:07:43 by pabalons         ###   ########.fr       */
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

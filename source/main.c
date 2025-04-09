/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penpalac <penpalac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/04/09 18:33:37 by penpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/minishell.h"

static void	ft_start_gigachell(void)
{
	signal(SIGINT, ft_handle_sigint);
	signal(SIGTERM, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

static int	ft_exec_line(char *line, char **envp, t_data *data)
{
	char	**mtx;
	t_ast	*ast;

	add_history(line);
	if (syntax_error(line) == ERROR)
		data->exit_status = 2;
	else
	{
		mtx = create_matrix(line, envp, data);
		if (!mtx && mtx == NULL)
		{
			ft_error("Error creating matrix\n");
			data->exit_status = 2;
		}
		ast = create_ast(mtx, envp);
		if (!ast)
		{
			ft_error("Error creating AST\n");
			data->exit_status = 2;
		}
		data->exit_status = execute_ast(ast);
		free_ast(ast);
		free_matrix(mtx);
	}
	return (data->exit_status);
}

static char *prompt_readline()
{
	char	*path;
	char	*prompt;

	path = ft_strjoin(GREEN ,getcwd(NULL, 0));
	prompt = ft_strjoin(path, "/");
	prompt = ft_strjoin(prompt, "Gigachell> "RST);
	free (path);
	return (prompt);
}

/**
 * Main function of the program
 */
int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	char	*line;
	char	**mtx;

	(void) argc;
	(void) argv;
	data.exit_status = 0;
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
		{
			data.exit_status = ft_exec_line(line, envp, &data);
			printf("exit: %d\n", data.exit_status);
		}
		free(line);
	}
	rl_clear_history();
	return (data.exit_status);
}

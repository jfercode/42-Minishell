/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penpalac <penpalac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 18:55:18 by jaferna2          #+#    #+#             */
/*   Updated: 2025/04/25 17:55:37 by penpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	ft_exec_line(char *line, t_data *data)
{
	char	**mtx;
	t_ast	*ast;

	if (line && line[0] != '\0')
		add_history(line);
	if (syntax_error(line) == ERROR)
		data->exit_status = 2;
	else
	{
		mtx = create_matrix(line, data);
		if (!mtx && mtx == NULL)
			return (0);
		ast = create_ast(mtx, data);
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

static int	run_non_interactive(t_data *data)
{
	char	*line;
	int		status;

	status = 0;
	line = ft_get_next_line(STDIN_FILENO);
	while (line != NULL)
	{
		status = ft_exec_line(line, data);
		free(line);
		line = ft_get_next_line(STDIN_FILENO);
	}
	free_data(data);
	return (status);
}

static int	run_interactive(t_data *data)
{
	int		status;
	char	*line;
	char	*prompt;

	status = 0;
	while (1)
	{
		ft_start_gigachell();
		prompt = ft_prompt_readline();
		line = readline(prompt);
		free(prompt);
		if (!line)
		{
			ft_printf(STDOUT_FILENO, "Leaving Gigachell...\n");
			break ;
		}
		status = ft_exec_line(line, data);
		free(line);
		if (data->exit)
			break ;
	}
	free_data(data);
	rl_clear_history();
	return (status);
}

/**
 * Main function of the program
 */
int	main(int argc, char **argv, char **envp)
{
	t_data	*data;
	char	*line;
	int		status;

	data = ft_calloc(1, sizeof(t_data));
	copy_envp(data, envp);
	if (!isatty(STDIN_FILENO))
		return (run_non_interactive(data));
	else
	{
		if (argc > 1)
		{
			if (ft_strncmp(argv[1], "-c", ft_strlen(argv[1])) == 0)
			{
				status = ft_exec_line(argv[2], data);
				free_data(data);
				return (status);
			}
		}
		else
			return (run_interactive(data));
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penpalac <penpalac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 17:07:15 by penpalac          #+#    #+#             */
/*   Updated: 2025/04/11 17:47:40 by penpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	ft_start_gigachell(void)
{
	signal(SIGINT, ft_handle_sigint);
	signal(SIGTERM, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

static char	**copy_envp(char **envp)
{
	char	**copy;
	int		i;

	i = 0;
	while (envp[i])
		i++;
	copy = malloc((i + 1) * sizeof(char *));
	if (!copy)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		copy[i] = ft_strdup(envp[i]);
		if (!copy[i])
			return (NULL);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

static int	ft_exec_line(char *line, t_data *data)
{
	char	**mtx;
	t_ast	*ast;

	add_history(line);
	if (syntax_error(line) == ERROR)
		data->exit_status = 2;
	else
	{
		mtx = create_matrix(line, data);
		if (!mtx && mtx == NULL)
		{
			ft_error("Error creating matrix\n");
			data->exit_status = 2;
		}
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

static char	*prompt_readline(void)
{
	char	*path;
	char	*prompt;

	path = ft_strjoin(GREEN, getcwd(NULL, 0));
	prompt = ft_strjoin(path, "/");
	prompt = ft_strjoin(prompt, "Gigachell> " RST);
	free(path);
	return (prompt);
}

/**
 * Main function of the program
 */
int	main(int argc, char **argv, char **envp)
{
	t_data	*data;
	char	*line;
	char	**mtx;

	data = ft_calloc(1, sizeof(t_data));
	data->envp = copy_envp(envp);
	if (argc == 2)
		data->exit_status = ft_exec_line(argv[1], data);
	while (1)
	{
		ft_start_gigachell();
		line = readline(prompt_readline());
		if (!line)
		{
			ft_printf(STDOUT_FILENO, "Leaving Gigachell...\n");
			break ;
		}
		data->exit_status = ft_exec_line(line, data);
		free(line);
		if (data->exit)
			break ;
	}
	free_data(data);
	rl_clear_history();
	return (data->exit_status);
}

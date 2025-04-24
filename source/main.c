/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaferna2 < jaferna2@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 18:55:18 by jaferna2          #+#    #+#             */
/*   Updated: 2025/04/24 17:13:27 by jaferna2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	ft_start_gigachell(void)
{
	struct sigaction	sa;

	signal(SIGINT, ft_handle_sigint_normal);
	signal(SIGTERM, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = ft_handle_sigint_normal;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		ft_error("Failed sigaction");
}

char	**copy_envp(char **envp)
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

static char	*prompt_readline(void)
{
	char	*cwd;
	char	*temp;
	char	*path;
	char	*prompt;

	cwd = getcwd(NULL, 0);
	path = ft_strjoin(GREEN, cwd);
	temp = ft_strjoin(path, "/");
	prompt = ft_strjoin(temp, "Gigachell> " RST);
	free(path);
	free(temp);
	free(cwd);
	return (prompt);
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
		prompt = prompt_readline();
		line = readline(prompt);
		free (prompt);
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
	data->envp = copy_envp(envp);
	if (!isatty(STDIN_FILENO))
		return (run_non_interactive(data));
	else
	{
		if (ft_strncmp(argv[1], "-c", ft_strlen(argv[1])) == 0)
		{
			status = ft_exec_line(argv[2], data);
			free_data(data);
			return (status);
		}
		return (run_interactive(data));
	}
}

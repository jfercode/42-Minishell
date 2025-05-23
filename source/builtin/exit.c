/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaferna2 <jaferna2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 16:42:38 by jaferna2          #+#    #+#             */
/*   Updated: 2025/04/29 17:25:32 by jaferna2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static bool	is_numeric(const char *str)
{
	int	i;

	if (!str || !*str)
		return (false);
	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (false);
		i++;
	}
	return (true);
}

static void	kill_all_ast_processes(t_ast *node)
{
	if (!node)
		return ;
	if (node->pid > 0)
	{
		kill(node->pid, SIGTERM);
		usleep(10000);
		if (waitpid(node->pid, NULL, WNOHANG) == 0)
		{
			kill(node->pid, SIGKILL);
			waitpid(node->pid, NULL, 0);
		}
	}
	kill_all_ast_processes(node->left);
	kill_all_ast_processes(node->right);
}

static void	close_ast_fds(t_ast *node)
{
	if (!node)
		return ;
	if (node->fd_infile > 2)
		close(node->fd_infile);
	if (node->fd_outfile > 2)
		close(node->fd_outfile);
	close_ast_fds(node->left);
	close_ast_fds(node->right);
}

int	ft_exit_more_args(t_ast *ast)
{
	if (!is_numeric(ast->args[1]))
	{
		close_ast_fds(ast);
		ast->data->exit = 1;
		return (2);
	}
	else
	{
		ft_error("exit\nbash: exit: too many arguments\n");
		return (1);
	}
}

int	ft_exit(t_ast *ast)
{
	int	arg_count;

	arg_count = 0;
	if (ast && ast->args)
		while (ast->args[arg_count])
			arg_count++;
	if (arg_count > 2)
		return (ft_exit_more_args(ast));
	if (arg_count == 2)
	{
		if (!is_numeric(ast->args[1]))
			ast->data->exit_status = 2;
		else
		{
			ast->data->exit_status = ft_atoi(ast->args[1]) % 256;
			if (ast->data->exit_status < 0)
				ast->data->exit_status += 256;
		}
	}
	close_ast_fds(ast);
	ast->data->exit = 1;
	return (ast->data->exit_status);
}

/*
int	ft_exit(t_ast *ast)
{
	int	exit_status;
	int	arg_count;

	exit_status = 0;
	arg_count = 0;
	if (ast && ast->args)
	{
		while (ast->args[arg_count])
			arg_count++;
	}
	if (arg_count > 2)
	{
		write(STDERR_FILENO, "exit: too many arguments\n", 24);
		return (1);
	}
	else if (arg_count == 2)
	{
		if (!is_numeric(ast->args[1]))
		{
			write(STDERR_FILENO, "exit: ", 6);
			write(STDERR_FILENO, ast->args[1], strlen(ast->args[1]));
			write(STDERR_FILENO, ": numeric argument required\n", 28);
			exit_status = 2;
		}
		else
		{
			exit_status = ft_atoi(ast->args[1]);
			exit_status = exit_status % 256;
			if (exit < 0)
				exit_status += 256;
		}
	}
	if (arg_count <= 2)
	{
		kill_all_ast_processes(ast);
		close_ast_fds(ast);
		free(ast);
		exit(exit_status);
	}
	return (0);
}
*/

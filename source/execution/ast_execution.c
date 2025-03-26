/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_execution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaferna2 <jaferna2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:54:36 by jaferna2          #+#    #+#             */
/*   Updated: 2025/03/25 18:39:26 by jaferna2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void prepare_redirecctions(t_ast *ast, int *fd_infile, int *fd_outfile)
{
	print_node(ast);
	if (ast == NULL)
		return ;
	if (ast->type == NODE_REDIR_IN)
		execute_redir_in_node(ast, fd_infile);
	else if (ast->type == NODE_HEREDOC)
		execute_heredoc_node(ast, fd_infile);
	else if (ast->type == NODE_REDIR_OUT)
		execute_redir_out_node(ast, fd_outfile);
	else if (ast->type == NODE_REDIR_APPEND)
		execute_redir_append_node(ast, fd_outfile);
	if (ast->left != NULL)
		prepare_redirecctions(ast->left, fd_infile, fd_outfile);
}

static void	execute_cmds_and_pipes(t_ast *ast)
{
	if (ast == NULL)
		return ;
	if (ast->type == NODE_PIPE)
		execute_pipe_node(ast);
	else if (ast->type == NODE_CMD)
		execute_cmd_node(ast);
	else
		execute_cmds_and_pipes(ast->left);
}

void	execute_ast(t_ast *ast)
{
	int	fd_infile;
	int	fd_outfile;
	int	original_stdin;
	int	original_stdout;

	original_stdin = dup(STDIN_FILENO);
	if (original_stdin == -1)
		ft_error("Error saving original STDIN");
	original_stdout = dup(STDOUT_FILENO);
	if (original_stdout == -1)
		ft_error("Error saving original STDOUT");

	fd_infile = STDIN_FILENO;
	fd_outfile = STDOUT_FILENO;

	prepare_redirecctions(ast, &fd_infile, &fd_outfile);

	if (fd_infile != STDIN_FILENO)
		if (dup2(fd_infile, STDIN_FILENO) == -1)
			ft_error_exit("Error duplicating file descriptor");
	if (fd_outfile != STDOUT_FILENO)
		if (dup2(fd_outfile, STDOUT_FILENO) == -1)
			ft_error_exit("Error duplicating file descriptor");

	execute_cmds_and_pipes(ast); // here run cmd 

	if (dup2(original_stdin, STDIN_FILENO) == -1)
		ft_error_exit("Error duplicating file descriptor");
	if (dup2(original_stdout, STDOUT_FILENO) == -1)
		ft_error_exit("Error duplicating file descriptor");
	
	close(original_stdin);
	close(original_stdout);
	
	if (fd_infile != STDIN_FILENO)
		close(fd_infile);
	if (fd_outfile != STDOUT_FILENO)
		close(fd_outfile);
}

int		obtain_ast_deep(t_ast *ast_root)
{
	t_ast	*current;
	int		i;

	current = ast_root;
	while (current->left)
	{
		current = current->left;
		i++;
	}
	return (i);
}

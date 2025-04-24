/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_execution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penpalac <penpalac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:54:36 by jaferna2          #+#    #+#             */
/*   Updated: 2025/04/24 18:50:44 by penpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Saves the current standard input and output file descriptors.
 *
 * This function duplicates the current STDIN and STDOUT file descriptors
 * and stores them in the provided pointers,
 * allowing them to be restored later.
 *
 * @param original_stdin  Pointer to an integer where the current STDIN file 
 * 							descriptor will be stored.
 * @param original_stdout Pointer to an integer where the current STDOUT file 
 * 							descriptor will be stored.
 */
static void	save_stdio(int *original_stdin, int *original_stdout)
{
	*original_stdin = dup(STDIN_FILENO);
	if (*original_stdin == -1)
		ft_error("Error saving original STDIN");
	*original_stdout = dup(STDOUT_FILENO);
	if (*original_stdout == -1)
		ft_error("Error saving original STDOUT");
}

/**
 * @brief Restores the original standard input and output file descriptors.
 *
 * This function replaces the current STDIN and STDOUT file descriptors
 * with the ones provided, effectively restoring them to their original state.
 * It also closes the provided file descriptors after restoring them.
 *
 * @param original_stdin  The file descriptor representing the original STDIN.
 * @param original_stdout The file descriptor representing the original STDOUT.
 */
static void	restore_stdio(int original_stdin, int original_stdout)
{
	if (dup2(original_stdin, STDIN_FILENO) == -1)
		ft_error_exit("Error restoring STDIN");
	if (dup2(original_stdout, STDOUT_FILENO) == -1)
		ft_error_exit("Error restoring STDOUT");
	close(original_stdin);
	close(original_stdout);
}

/**
 * @brief Executes redirection nodes in an abstract syntax tree (AST).
 *
 * This function recursively traverses and executes redirection-related nodes
 * in the given AST. It handles various types of redirection, including heredocs,
 * input redirection, output redirection, and output append redirection.
 *
 * @param node       Pointer to the current AST node to process.
 * @param fd_infile  Pointer to an integer where the input file descriptor 
 * 						will be stored if applicable.
 * @param fd_outfile Pointer to an integer where the output file descriptor
 * 						 will be stored if applicable.
 * @param fd         Pointer to an integer used to manage temporary
 * 						 file descriptors (e.g., heredocs).
 *
 * @return 0 on success, or ERROR on failure.
 */
int	execute_redirection_node(t_ast *node, int *fd_infile, int *fd_outfile,
		int *fd)
{
	if (!node)
		return (ERROR);
	if (node->left && execute_redirection_node(node->left, fd_infile,
			fd_outfile, fd) == ERROR)
		return (ERROR);
	if (node->type == NODE_HEREDOC && execute_heredoc_node(node, fd_infile,
			fd) == ERROR)
		return (ERROR);
	else if (node->type == NODE_REDIR_IN && execute_redir_in_node(node,
			fd_infile, fd) == ERROR)
		return (ERROR);
	else if (node->type == NODE_REDIR_OUT && execute_redir_out_node(node,
			fd_outfile, fd) == ERROR)
		return (ERROR);
	else if (node->type == NODE_REDIR_APPEND && execute_redir_append_node(node,
			fd_outfile, fd) == ERROR)
		return (ERROR);
	return (0);
}

/**
 * @brief Executes a node in the abstract syntax tree (AST).
 *
 * This function determines the type of the AST node and dispatches execution 
 * accordingly. It supports command execution, piping, and various types of
 * redirection, including heredoc, input, output, and append redirections.
 * 
 * Redirection nodes are resolved recursively, and the corresponding file 
 * descriptors are applied to STDIN and STDOUT as needed.
 *
 * @param node        Pointer to the AST node to execute.
 * @param fd_infile   Pointer to an integer representing the input fd.
 * @param fd_outfile  Pointer to an integer representing the output fd.
 */
static int	execute_node(t_ast *node, int *fd_infile, int *fd_outfile)
{
	int	fd;

	fd = 7;
	if (!node)
		node->data->exit_status = waitpid(-1, &node->data->exit_status, 0);
	if (node->type == NODE_PIPE)
		execute_pipe_node(node);
	else if (node->type == NODE_HEREDOC || node->type == NODE_REDIR_IN
		|| node->type == NODE_REDIR_OUT || node->type == NODE_REDIR_APPEND)
	{
		if (execute_redirection_node(node, fd_infile, fd_outfile, &fd) == ERROR)
		{
			if (*fd_infile != STDIN_FILENO)
				close(*fd_infile);
			if (*fd_outfile != STDOUT_FILENO)
				close(*fd_outfile);
			node->data->exit_status = waitpid(-1, &node->data->exit_status, 0);
		}
		while (node->left)
		{
			if (node->left->type != NODE_CMD)
				node = node->left;
			else
				break ;
		}
		if (dup2(*fd_infile, STDIN_FILENO) == -1)
			ft_error_exit("Error duplicating STDIN");
		if (dup2(*fd_outfile, STDOUT_FILENO) == -1)
			ft_error_exit("Error duplicating STDOUT");
		if (node->left)
			execute_node(node->left, fd_infile, fd_outfile);
		if (node->right)
			execute_node(node->right, fd_infile, fd_outfile);
	}
	else if (node->type == NODE_CMD)
		execute_cmd_node(node);
	return (node->data->exit_status);
}

/**
 * @brief Executes the given abstract syntax tree (AST).
 *
 * This function serves as the entry point for executing an AST.
 * It saves the current standard input and output, sets up the necessary
 * file descriptors, executes the AST recursively, and restores the original
 * standard I/O afterward. Any modified input/output file descriptors are closed
 * after execution.
 *
 * @param ast Pointer to the root node of the AST to execute.
 */
int	execute_ast(t_ast *ast)
{
	int	fd_infile;
	int	fd_outfile;
	int	original_stdin;
	int	original_stdout;

	save_stdio(&original_stdin, &original_stdout);
	fd_infile = STDIN_FILENO;
	fd_outfile = STDOUT_FILENO;
	ast->data->exit_status = execute_node(ast, &fd_infile, &fd_outfile);
	restore_stdio(original_stdin, original_stdout);
	if (fd_infile != STDIN_FILENO)
		close(fd_infile);
	if (fd_outfile != STDOUT_FILENO)
		close(fd_outfile);
	return (ast->data->exit_status);
}

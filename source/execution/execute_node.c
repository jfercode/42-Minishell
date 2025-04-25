/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_node.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaferna2 < jaferna2@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 11:48:29 by jaferna2          #+#    #+#             */
/*   Updated: 2025/04/25 12:06:26 by jaferna2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Waits for any child process to terminate and updates the 
 * shared exit status.
 *
 * This function calls waitpid on any child (-1) 
 * and stores the returned status in the given data structure. 
 * If waitpid fails, it exits the program with an error.
 *
 * @param data Pointer to the global data structure, 
 * whose exit_status field will be updated.
 */
void	wait_for_children_node(t_data *data)
{
	if (waitpid(-1, &data->exit_status, 0) == -1)
		ft_error_exit("waitpid failed");
}

/**
 * @brief Handles the execution of a pipeline node in the AST.
 *
 * This function dispatches the pipeline execution logic for a NODE_PIPE.
 * It simply calls the lower-level execute_pipe_node function and returns
 * the resulting exit status.
 *
 * @param node AST node of type NODE_PIPE.
 * @return The exit status produced by execute_pipe_node.
 */
int	handle_pipe_node(t_ast *node)
{
	execute_pipe_node(node);
	return (node->data->exit_status);
}

/**
 * @brief Applies redirected file descriptors and recurses into
 *  child nodes.
 *
 * After redirections have been set up, this helper duplicates 
 * the input and output file descriptors onto STDIN and STDOUT
 * respectively, then executes any remaining left and right
 * subtrees.
 *
 * @param node    AST node from which to continue execution.
 * @param fd_in   Pointer to the current input file descriptor.
 * @param fd_out  Pointer to the current output file descriptor.
 * @return        The exit status after executing both subtrees.
 */
int	apply_and_recurse(t_ast *node, int *fd_in, int *fd_out)
{
	if (dup2(*fd_in, STDIN_FILENO) == -1
		|| dup2(*fd_out, STDOUT_FILENO) == -1)
		ft_error_exit("dup2 failed");
	if (node->left)
		execute_node(node->left, fd_in, fd_out);
	if (node->right)
		execute_node(node->right, fd_in, fd_out);
	return (node->data->exit_status);
}

/**
 * @brief Handles all types of redirection nodes.
 *
 * Sets up the necessary redirections by calling 
 * execute_redirection_node.
 * On error, it cleans up any opened file descriptors and waits 
 * for children.
 * 
 * Then it descends to the innermost command node and applies 
 * the redirection before recursing.
 *
 * @param node    AST node representing a redirection.
 * @param fd_in   Pointer to the current input file descriptor.
 * @param fd_out  Pointer to the current output file descriptor.
 * @return        The exit status after applying redirections.
 */
int	handle_redir_node(t_ast *node, int *fd_in, int *fd_out)
{
	int	fd;

	fd = 7;
	if (execute_redirection_node(node, fd_in, fd_out, &fd) == ERROR)
	{
		if (*fd_in != STDIN_FILENO)
			close(*fd_in);
		if (*fd_out != STDOUT_FILENO)
			close(*fd_out);
		wait_for_children_node(node->data);
	}
	while (node->left && node->left->type != NODE_CMD)
		node = node->left;
	return (apply_and_recurse(node, fd_in, fd_out));
}

/**
 * @brief Executes a simple command node in the AST.
 *
 * Delegates to execute_cmd_node to perform the actual fork/exec.
 *
 * @param node AST node of type NODE_CMD.
 * @return     The exit status from the executed command.
 */
int	handle_cmd_node(t_ast *node)
{
	execute_cmd_node(node);
	return (node->data->exit_status);
}

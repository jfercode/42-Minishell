/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_execution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penpalac <penpalac@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:54:36 by jaferna2          #+#    #+#             */
/*   Updated: 2025/03/31 16:32:51 by penpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * TO DO: PREPARAR LA MALDITA EJECUCION DE NUESTRO MARAVILLOSO AST
 * VA A SER SIMILAR A EL PRINT_AST EN CUANTO A COMO VA A IR RECORRIENDO
 * LA ESTRUCTURA Y BUSCO HACER QUE:
 *	-> SI ESTA EN UN NODO PIPE, PREPARE LOS PIPES
	-> SI ESTA EN UN NODO DE REDIRECCION TENGO QUE EJECUTAR LA REDIRECCION
	-> NODO COMANDO SE EJECUTA EL COMANDO
	POR LO TANTO TENGO QUE COGER LAS FUNCIONES Y PREPARARLAS PARA QUE PASEN
	CORRECTAMENTE SEGÚN EL TIPO DE NODO QUE SEA. 
	REVISAR EL PUTO CODIGO QUE YA ETAAAAAAAAAAAAAAAAAAAAAAAAAAA
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

static void	save_stdio(int *original_stdin, int *original_stdout)
{
	*original_stdin = dup(STDIN_FILENO);
	if (*original_stdin == -1)
		ft_error("Error saving original STDIN");
	*original_stdout = dup(STDOUT_FILENO);
	if (*original_stdout == -1)
		ft_error("Error saving original STDOUT");
}

static void	execute_redirection_node(t_ast *node,
					int *fd_infile, int *fd_outfile)
{
	if (node == NULL)
		return ;
	if (node->left != NULL)
		execute_redirection_node(node->left, fd_infile, fd_outfile);
	if (node->type == NODE_HEREDOC)
		execute_heredoc_node(node, fd_infile);
	else if (node->type == NODE_REDIR_IN)
		execute_redir_in_node(node, fd_infile);
	else if (node->type == NODE_REDIR_OUT)
		execute_redir_out_node(node, fd_outfile);
	else if (node->type == NODE_REDIR_APPEND)
		execute_redir_append_node(node, fd_outfile);
}

static void	execute_node(t_ast *node, int *fd_infile, int *fd_outfile)
{
	if (!node)
		return ;
	if (node->type == NODE_PIPE)
		execute_pipe_node(node); // PREPARAR LOS PIPES AQUÍ
	else if (node->type == NODE_HEREDOC || node->type == NODE_REDIR_IN
		|| node->type == NODE_REDIR_OUT || node->type == NODE_REDIR_APPEND)
	{
		execute_redirection_node(node, fd_infile, fd_outfile);
		while (node->left->type != NODE_CMD)
			node = node->left;
		if (dup2(*fd_infile, STDIN_FILENO) == -1)
			ft_error_exit("Error duplicating STDIN");
		if (dup2(*fd_outfile, STDOUT_FILENO) == -1)
			ft_error_exit("Error duplicating STDOUT");
	}
	else if (node->type == NODE_CMD)
	{
		execute_cmd_node(node);
		return ;
	}
	if (node->left)
		execute_node(node->left, fd_infile, fd_outfile);
	if (node->right)
		execute_node(node->right, fd_infile, fd_outfile);
}

void	execute_ast(t_ast *ast)
{
	int	fd_infile;
	int	fd_outfile;
	int	original_stdin;
	int	original_stdout;

	save_stdio(&original_stdin, &original_stdout);
	fd_infile = STDIN_FILENO;
	fd_outfile = STDOUT_FILENO;
	execute_node(ast, &fd_infile, &fd_outfile);
	restore_stdio(original_stdin, original_stdout);
	if (fd_infile != STDIN_FILENO)
		close(fd_infile);
	if (fd_outfile != STDOUT_FILENO)
		close(fd_outfile);
}

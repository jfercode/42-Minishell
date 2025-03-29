/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_execution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaferna2 <jaferna2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:54:36 by jaferna2          #+#    #+#             */
/*   Updated: 2025/03/29 13:07:49 by jaferna2         ###   ########.fr       */
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
 */

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

	execute_cmds_and_pipes(ast);

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

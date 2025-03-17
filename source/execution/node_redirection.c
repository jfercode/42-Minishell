/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaferna2 <jaferna2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:43:42 by jaferna2          #+#    #+#             */
/*   Updated: 2025/03/17 18:10:56 by jaferna2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Usar función handle heredoc aqui y actualizar como infile en la ejecución al
 * heredoc
 */
void	execute_heredoc_node(t_ast *node)
{
	
}

/**
 * Comprobar que existe el archivo, abrirlo con los permisos necesarios y 
 * actualizar como infile en la ejecución 
 */
void	execute_redir_in_node(t_ast *node)
{
	
}

/**
 * - Comprobar si existe el archivo
 * 		-> Si existe - NULL
 * 		-> No existe - crear el archivo
 * - abrirlo en modo O_TRUNC
 * - actualizar el archivo a outfile en ejecución
 */
void	execute_redir_out_node(t_ast *node)
{
	
}
/**
 * - Comprobar si existe el archivo
 * 		-> Si existe - NULL
 * 		-> No existe - crear el archivo
 * - abrirlo en modo O_APPEND
 * - actualizar el archivo a outfile en ejecución
 */
void	execute_redir_append_node(t_ast *node)
{
	
}

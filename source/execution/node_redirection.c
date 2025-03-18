/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaferna2 <jaferna2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:43:42 by jaferna2          #+#    #+#             */
/*   Updated: 2025/03/18 17:29:25 by jaferna2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Usar función handle heredoc aqui y actualizar como infile en la ejecución al
 * heredoc
 */
void	execute_heredoc_node(t_ast *node)
{
	int 	fd;
	int		i;
	char	*line;

	fd = 0;
	i = 0;
	if (node->type != NODE_HEREDOC)
		return ;
	fd = ft_handle_here_doc(node->args[1]);
	ft_read_fd("/tmp/manopla.txt"); // TO DO ELIMINAR
}

/**
 * Comprobar que existe el archivo, abrirlo con los permisos necesarios y 
 * actualizar como infile en la ejecución 
 */
void	execute_redir_in_node(t_ast *node)
{
	if (node->type != NODE_REDIR_IN)
		return ;
	ft_read_fd(node->args[1]);
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
	if (node->type != NODE_REDIR_OUT)
		return ;
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
	if (node->type != NODE_REDIR_APPEND)
		return ;	
}

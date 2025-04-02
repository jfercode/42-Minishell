/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penpalac <penpalac@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:43:42 by jaferna2          #+#    #+#             */
/*   Updated: 2025/04/02 18:21:10 by penpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Usar función handle heredoc aqui y actualizar como infile en la ejecución al
 * heredoc
 */
void	execute_heredoc_node(t_ast *node, int *fd_heredoc)
{
	int	new_fd;
	int	fd;

	if (node->type != NODE_HEREDOC)
		return ;
	if (*fd_heredoc != STDIN_FILENO)
		close(*fd_heredoc);
	ft_handle_here_doc(node->args[1]);
	fd = open("/tmp/heredoc_tmp.txt", O_RDONLY);
	if (fd == -1)
		ft_error("Error opening file");
	if (fd == 5 || fd == 6)
	{
		new_fd = dup2(fd, 7);
		if (new_fd == -1)
			ft_error("Error duplicating file descriptor");
		close(fd);
		fd = new_fd;
	}
	*fd_heredoc = fd;
}

/**
 * Comprobar que existe el archivo, abrirlo con los permisos necesarios y
 * actualizar como infile en la ejecución
 */
void	execute_redir_in_node(t_ast *node, int *fd_infile)
{
	int	new_fd;
	int	fd;

	if (node->type != NODE_REDIR_IN)
		return ;
	if (*fd_infile != STDIN_FILENO)
		close(*fd_infile);
	fd = open(node->args[1], O_RDONLY);
	if (fd == -1)
		ft_error("Error opening file");
	if (fd == 5 || fd == 6)
	{
		new_fd = dup2(fd, 7);
		if (new_fd == -1)
			ft_error("Error duplicating file descriptor");
		close(fd);
		fd = new_fd;
	}
	*fd_infile = fd;
}

/**
 * - Comprobar si existe el archivo
 * 		-> Si existe - NULL
 * 		-> No existe - crear el archivo
 * - abrirlo en modo O_TRUNC
 * - actualizar el archivo a outfile en ejecución
 */
void	execute_redir_out_node(t_ast *node, int *fd_outfile)
{
	int	new_fd;
	int	fd;

	if (node->type != NODE_REDIR_OUT)
		return ;
	if (*fd_outfile != STDOUT_FILENO)
		close(*fd_outfile);
	fd = open(node->args[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		ft_error("Error opening file");
	if (fd == 5 || fd == 6)
	{
		new_fd = dup2(fd, 7);
		if (new_fd == -1)
			ft_error("Error duplicating file descriptor");
		close(fd);
		fd = new_fd;
	}
	*fd_outfile = fd;
}

/**
 * - Comprobar si existe el archivo
 * 		-> Si existe - NULL
 * 		-> No existe - crear el archivo
 * - abrirlo en modo O_APPEND
 * - actualizar el archivo a outfile en ejecución
 */
void	execute_redir_append_node(t_ast *node, int *fd_outfile)
{
	int	new_fd;
	int	fd;

	if (node->type != NODE_REDIR_APPEND)
		return ;
	if (*fd_outfile != STDOUT_FILENO)
		close(*fd_outfile);
	fd = open(node->args[1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		ft_error("Error opening file");
	if (fd == 5 || fd == 6)
	{
		new_fd = dup2(fd, 7);
		if (new_fd == -1)
			ft_error("Error duplicating file descriptor");
		close(fd);
		fd = new_fd;
	}
	*fd_outfile = fd;
}

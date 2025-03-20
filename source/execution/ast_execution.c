/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_execution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaferna2 <jaferna2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:54:36 by jaferna2          #+#    #+#             */
/*   Updated: 2025/03/20 19:05:04 by jaferna2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * 	TO DO:	redirecciones y pipe (en pipe simplemente con lo que tenga de la
 * 			anterior ejecucion pipear lo que ya tenga).
 */
int		execute_ast(t_ast *ast)
{
	t_ast			*current;
	static int		fd_infile = STDIN_FILENO;
	static int		fd_outfile = STDOUT_FILENO;

	current = ast;
	if (current->left != NULL)
		current = current->left;
	if (current->type == NODE_CMD)
		execute_cmd_node(current, fd_infile, fd_outfile);
	// else if (current->type == NODE_PIPE)
	// 	// EXECUTE PIPE (right & left nodes)
	// else if (current->type == NODE_REDIR_IN)
	// 	// EXECUTE REDIR_IN NODE (open the file)
	// else if (current->type == NODE_HEREDOC)
	// 	// EXECUTE NODE_HEREDOC (handle heredoc and setted as fd in)
	// else if (current->type == NODE_REDIR_OUT)
	// 	// EXECUTE NODE_REDIR_OUT (Open / create the file and sustitude the fd_out)
	// else if (current->type == NODE_REDIR_APPEND)
	// 	// EXECUTE NODE_REDIR_APPEND (Same as redir out but in append mode)
	return (1);
}

/**
 * @brief			function that travels around the ast to count the deep of itself
 * 
 * @param ast_root	the ast root
 * @return			returns a integer with the ast "deep";
 */
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_execution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaferna2 <jaferna2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:54:36 by jaferna2          #+#    #+#             */
/*   Updated: 2025/03/17 17:41:55 by jaferna2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Aqui necesito ir recorriendo el AST, una primera vez para 
//  */
// int		execute_ast(t_ast *ast)
// {
	// int		fd_infile;
	// int		fd_outfile;

	// if ((*ast).type == NODE_CMD)
		// // EXECUTE CMD NODE
	// else if ((*ast).type == NODE_PIPE)
		// // EXECUTE PIPE (right & left nodes)
	// else if ((*ast).type == NODE_REDIR_IN)
		// // EXECUTE REDIR_IN NODE (open the file)
	// else if ((*ast).type == NODE_HEREDOC)
		// // EXECUTE NODE_HEREDOC (handle heredoc and setted as fd in)
	// else if ((*ast).type == NODE_REDIR_OUT)
		// // EXECUTE NODE_REDIR_OUT (Open / create the file and sustitude the fd_out)
	// else if ((*ast).type == NODE_REDIR_APPEND)
		// // EXECUTE NODE_REDIR_APPEND (Same as redir out but in append mode)
	
// }

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

	/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_execution_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaferna2 < jaferna2@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:45:26 by penpalac          #+#    #+#             */
/*   Updated: 2025/04/23 16:45:33 by jaferna2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	order_cmds(t_ast *node, t_ast **cmds)
{
	t_ast	*temp;
	t_ast	*current;
	int		i;
	int		j;

	i = 0;
	current = node;
	while (current && current->type == NODE_PIPE)
	{
		if (!current->right)
			break ;
		cmds[i++] = current->right;
		current = current->left;
	}
	if (current)
		cmds[i++] = current;
	cmds[i] = NULL;
	j = 0;
	while (j < i / 2)
	{
		temp = cmds[j];
		cmds[j] = cmds[i - 1 - j];
		cmds[i - 1 - j] = temp;
		j++;
	}
}

void	setup_redirections(t_ast *node, int *fd_in, int *fd_out)
{
	if (*fd_in != STDIN_FILENO)
		dup2(*fd_in, STDIN_FILENO);
	if (*fd_out != STDOUT_FILENO)
		dup2(*fd_out, STDOUT_FILENO);
	if (node->fd_infile != STDIN_FILENO)
	{
		dup2(node->fd_infile, STDIN_FILENO);
		close(node->fd_infile);
	}
	if (node->fd_outfile != STDOUT_FILENO)
	{
		dup2(node->fd_outfile, STDOUT_FILENO);
		close(node->fd_outfile);
	}
	if (*fd_in != STDIN_FILENO)
		close(*fd_in);
	if (*fd_out != STDOUT_FILENO)
		close(*fd_out);
}

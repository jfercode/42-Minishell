/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaferna2 <jaferna2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 17:52:44 by jaferna2          #+#    #+#             */
/*   Updated: 2025/02/26 18:58:57 by jaferna2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_node(t_ast *node)
{
	int	i;

	if (node->type == NODE_CMD)
		printf(GREEN"type: "RST"CMD\n");
	else if (node->type == NODE_PIPE)
		printf(GREEN"type: "RST"PIPE\n");
	else if (node->type == NODE_HEREDOC)
		printf(GREEN"type: "RST"HEREDOC\n");
	else if (node->type == NODE_REDIR_IN)
		printf(GREEN"type: "RST"REDIR_IN\n");
	else if (node->type == NODE_REDIR_OUT)
		printf(GREEN"type: "RST"REDIR_OUT\n");
	else if (node->type == NODE_REDIR_APPEND)
		printf(GREEN"type: "RST"REDIR_OUT\n");
	printf(GREEN"token: "RST"%s\n", node->args[0]);
	if (node->args)
	{
		i = 0;
		while (node->args[i])
		{
			printf(GREEN"token arg["RST"%d"GREEN"]: "RST"%s\n",
				i, node->args[i]);
			i++;
		}
	}
}

void	print_ast(t_ast *root, int level)
{
	int				i;
	t_ast			*current;

	current = root;
	i = 0;
	print_node(current);
	if (current->left)
	{
		printf(BLUE"left:\n"RST);
		print_ast(current->left, level + 1);
	}
	if (current->right)
	{
		printf(BLUE"right:\n"RST);
		print_ast(current->right, level + 1);
	}
}

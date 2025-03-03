/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaferna2 <jaferna2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 17:52:44 by jaferna2          #+#    #+#             */
/*   Updated: 2025/03/03 19:04:23 by jaferna2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * @brief Prints information about a given AST node.
 *
 * This function prints the type of the node and its associated tokens.
 * It uses color-coded output for readability.
 *
 * @param node Pointer to the AST node to print.
 */
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

/**
 * @brief Recursively prints the structure of an AST.
 *
 * This function traverses the AST and prints each node along with its
 * left and right children. It helps visualize the tree structure.
 *
 * @param root Pointer to the root of the AST.
 * @param level Current depth level in the AST (used for indentation).
 */
void	print_ast(t_ast *root, int level)
{
	int				i;
	t_ast			*current;

	current = root;
	i = 0;
	print_node(current);
	if (current->left)
	{
		printf(BLUE"left_%s:\n"RST, current->args[0]);
		print_ast(current->left, level + 1);
	}
	if (current->right)
	{
		printf(BLUE"right_%s:\n"RST, current->args[0]);
		print_ast(current->right, level + 1);
	}
}

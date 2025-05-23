/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaferna2 < jaferna2@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 11:25:15 by pablo             #+#    #+#             */
/*   Updated: 2025/04/25 12:05:35 by jaferna2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	handle_pipe_node_tk(t_ast **root, t_ast *new_node)
{
	if (*root)
		new_node->left = *root;
	*root = new_node;
}

static void	handle_redirect_node_tk(t_ast **root, t_ast *new_node)
{
	if (*root != NULL)
	{
		if ((*root)->type == NODE_PIPE)
		{
			if ((*root)->right == NULL)
				(*root)->right = new_node;
			else
			{
				new_node->left = (*root)->right;
				(*root)->right = new_node;
			}
		}
		else if ((*root)->type != NODE_PIPE)
		{
			new_node->left = *root;
			*root = new_node;
		}
	}
	else
		*root = new_node;
}

static void	insert_cmd_right(t_ast *parent, t_ast *new_node)
{
	t_ast	*current;

	current = parent;
	while (current->right)
		current = current->right;
	current->right = new_node;
}

static void	handle_cmd_node_tk(t_ast **root, t_ast *new_node)
{
	t_ast	*current;

	if (!*root)
		*root = new_node;
	else if (*root && (*root)->type == NODE_PIPE)
	{
		if ((*root)->right == NULL)
			(*root)->right = new_node;
		else
			insert_cmd_right((*root)->right, new_node);
	}
	else if (*root && (*root)->type != NODE_PIPE)
	{
		current = (*root);
		while (current->left)
			current = current->left;
		current->left = new_node;
	}
}

/**
 * @brief Creates an Abstract Syntax Tree (AST) from a list of tokens.
 *
 * This function iterates through the given tokens and constructs an AST
 * by linking nodes based on their token types. Command nodes are added
 * as leaves, while operator nodes (such as pipes or redirections) are
 * placed as intermediate nodes.
 *
 * @param tokens A null-terminated array of strings representing tokens.
 * @return A pointer to the root of the constructed AST.
 */
t_ast	*create_ast(char **tokens, t_data *data)
{
	t_ast	*root;
	t_ast	*new_node;
	t_ast	*current;
	int		i;

	root = NULL;
	current = NULL;
	i = 0;
	while (tokens[i])
	{
		new_node = create_node(tokens, data, &i);
		if (!new_node)
			return (free_ast(root), NULL);
		if (new_node->type == NODE_PIPE)
			handle_pipe_node_tk(&root, new_node);
		else if (new_node->type == NODE_REDIR_IN
			|| new_node->type == NODE_REDIR_OUT
			|| new_node->type == NODE_REDIR_APPEND
			|| new_node->type == NODE_HEREDOC)
			handle_redirect_node_tk(&root, new_node);
		else if (new_node->type == NODE_CMD)
			handle_cmd_node_tk(&root, new_node);
	}
	return (root);
}

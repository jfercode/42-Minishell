/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaferna2 <jaferna2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 17:44:52 by jaferna2          #+#    #+#             */
/*   Updated: 2025/03/26 18:37:28 by jaferna2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_ast *find_last_pipe(t_ast *node)
{
	t_ast *current;

	current = node;
	while (current)
	{
		if (current->type == NODE_PIPE && current->right == NULL)
			return (current);
		current = current->left;
	}
	return (NULL);
}

static void	handle_pipe_node(t_ast **root, t_ast *new_node)
{
	if (*root)
		new_node->left = *root;
	*root = new_node;	
}

static void handle_redirect_node(t_ast **root, t_ast *new_node)
{
	t_ast *last_pipe;

	last_pipe = find_last_pipe(*root);
	if (last_pipe)
	{
		if (last_pipe->right == NULL)
			last_pipe->right = new_node;
		else
		{
			new_node->left = last_pipe->right;
			last_pipe->right = new_node;
		}
	}
	else
	{
		new_node->left = *root;
		*root = new_node;
	}
}

static void handle_cmd_node(t_ast **root, t_ast *new_node)
{
	t_ast	*last_pipe;
	t_ast	*current;
	
	last_pipe = find_last_pipe(*root);
	if (last_pipe)
	{
		if (last_pipe->right == NULL)
			last_pipe->right = new_node;
		else
		{
			current = last_pipe->right;
			while (current->left)
				current = current->left;
			current->left = new_node;
		}
	}
	else
	{
		if (!*root)
			*root = new_node;
		else
		{
			current = *root;
			while (current->left)
				current = current->left;
			current->left = new_node;
		}
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
t_ast	*create_ast(char **tokens, char **envp)
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
		new_node = create_node(tokens, envp, &i);
		if (!new_node)
			return (free_ast(root), NULL);
		if (new_node->type == NODE_PIPE)
			handle_pipe_node(&root, new_node);
		else if (new_node->type == NODE_REDIR_IN || new_node->type == NODE_REDIR_OUT
				|| new_node->type == NODE_REDIR_APPEND || new_node->type == NODE_HEREDOC)
			handle_redirect_node(&root, new_node);
		else if (new_node->type == NODE_CMD)
			handle_cmd_node(&root, new_node);
	}
	return (root);
}

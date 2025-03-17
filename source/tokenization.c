/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penpalac <penpalac@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 17:44:52 by jaferna2          #+#    #+#             */
/*   Updated: 2025/03/17 18:20:29 by penpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * @brief Creates a new AST node from the given arguments.
 *
 * This function allocates memory for a new AST node and determines its type
 * based on the provided tokens. If the node is a command, it collects all
 * consecutive command tokens. Ot1herwise, it handles a single operator token.
 *
 * @param args A null-terminated array of strings representing tokens.
 * @param indx A pointer to the current index in the token array, updated as
 * tokens are processed.
 * @return A pointer to the newly created AST node, or NULL if allocation fails.
 */
t_ast	*create_node(char **args, int *indx)
{
	t_ast	*node;
	int		i;
	int		j;

	i = *indx;
	j = 0;
	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = get_token_type(args[i]);
	if (node->type == NODE_CMD)
		while (args[i] && get_token_type(args[i]) == NODE_CMD)
			i++;
	else if (node->type == NODE_REDIR_OUT || node->type == NODE_REDIR_IN
		|| node->type == NODE_HEREDOC || node->type == NODE_REDIR_APPEND)
		i = *indx + 2;
	else
		i = *indx + 1;
	node->args = malloc(sizeof(char *) * (i - *indx + 1));
	if (!node->args)
		return (free_node(node), NULL);
	while (*indx < i)
		node->args[j++] = ft_strdup(args[(*indx)++]);
	node->args[j] = NULL;
	node->right = NULL;
	node->left = NULL;
	return (node);
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
t_ast	*create_ast(char **tokens)
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
		new_node = create_node(tokens, &i);
		if (!new_node)
			return (free_ast(root), NULL);
		if (new_node->type == NODE_CMD)
		{
			if (current && current->type != NODE_CMD)
				current->right = new_node;
		}
		else
			new_node->left = root;
		if (!root || new_node->type != NODE_CMD)
			root = new_node;
		current = new_node;
	}
	return (root);
}

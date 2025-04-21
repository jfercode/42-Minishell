/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaferna2 < jaferna2@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 18:47:13 by jaferna2          #+#    #+#             */
/*   Updated: 2025/04/21 18:47:48 by jaferna2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Determines the type of node based on the given token.
 *
 * This function compares the provided token with predefined symbols
 * and returns the corresponding node type.
 *
 * @param token A null-terminated string representing a token.
 * @return The corresponding node type as a t_node_type enumeration.
 */
t_node_type	get_token_type(char *token)
{
	if (ft_strncmp(token, "|", ft_strlen(token)) == 0)
		return (NODE_PIPE);
	else if (ft_strncmp(token, "<", ft_strlen(token)) == 0)
		return (NODE_REDIR_IN);
	else if (ft_strncmp(token, "<<", ft_strlen(token)) == 0)
		return (NODE_HEREDOC);
	else if (ft_strncmp(token, ">", ft_strlen(token)) == 0)
		return (NODE_REDIR_OUT);
	else if (ft_strncmp(token, ">>", ft_strlen(token)) == 0)
		return (NODE_REDIR_APPEND);
	else
		return (NODE_CMD);
}

/**
 * @brief Frees the memory allocated for a single AST node.
 *
 * This function releases the memory associated with a given AST node,
 * including its arguments array and the node itself.
 *
 * @param node A pointer to the AST node to be freed.
 */
void	free_node(t_ast *node)
{
	int	i;

	i = 0;
	if (!node)
		return ;
	if (node->args)
	{
		while (node->args[i])
			free(node->args[i++]);
		free(node->args);
	}
	free(node);
}

/**
 * @brief Recursively frees the memory allocated for an AST.
 *
 * This function traverses the AST in post-order and releases the memory
 * associated with each node, including its left and right children.
 *
 * @param root A pointer to the root node of the AST to be freed.
 */
void	free_ast(t_ast *root)
{
	if (!root)
		return ;
	free_ast(root->left);
	free_ast(root->right);
	free_node(root);
}

void	free_data(t_data *data)
{
	int	i;

	if (!data || !data->envp)
		return ;
	i = 0;
	while (data->envp[i])
	{
		free(data->envp[i]);
		i++;
	}
	free(data->envp);
	data->envp = NULL;
}

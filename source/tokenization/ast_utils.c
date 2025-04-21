/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaferna2 < jaferna2@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 17:52:44 by jaferna2          #+#    #+#             */
/*   Updated: 2025/04/21 16:43:41 by jaferna2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static	int	obtain_current_indx_token(int *indx, char **args, t_node_type type)
{
	int	i;

	i = *indx;
	if (type == NODE_CMD)
		while (args[i] && get_token_type(args[i]) == NODE_CMD)
			i++;
	else if (type == NODE_REDIR_OUT || type == NODE_REDIR_IN
		|| type == NODE_HEREDOC || type == NODE_REDIR_APPEND)
		i = *indx + 2;
	else
		i = *indx + 1;
	return (i);
}

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
t_ast	*create_node(char **args, char **envp, int *indx)
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
	i = obtain_current_indx_token(indx, args, node->type);
	node->args = malloc(sizeof(char *) * (i - *indx + 1));
	if (!node->args)
		return (free_node(node), NULL);
	while (*indx < i)
		node->args[j++] = ft_strdup(args[(*indx)++]);
	node->envp = envp;
	node->args[j] = NULL;
	node->right = NULL;
	node->left = NULL;
	node->fd_infile = STDIN_FILENO;
	node->fd_outfile = STDOUT_FILENO;
	node->exit_status = 0;
	return (node);
}

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
		ft_printf(STDOUT_FILENO, GREEN "type: " RST "CMD\n");
	else if (node->type == NODE_PIPE)
		ft_printf(STDOUT_FILENO, GREEN "type: " RST "PIPE\n");
	else if (node->type == NODE_HEREDOC)
		ft_printf(STDOUT_FILENO, GREEN "type: " RST "HEREDOC\n");
	else if (node->type == NODE_REDIR_IN)
		ft_printf(STDOUT_FILENO, GREEN "type: " RST "REDIR_IN\n");
	else if (node->type == NODE_REDIR_OUT)
		ft_printf(STDOUT_FILENO, GREEN "type: " RST "REDIR_OUT\n");
	else if (node->type == NODE_REDIR_APPEND)
		ft_printf(STDOUT_FILENO, GREEN "type: " RST "REDIR_OUT\n");
	printf(GREEN "token: " RST "%s\n", node->args[0]);
	if (node->args)
	{
		i = 0;
		while (node->args[i])
		{
			ft_printf(STDOUT_FILENO, GREEN"token arg[" RST "%d" GREEN "]: "
				RST "%s\n", i, node->args[i]);
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
	int		i;
	t_ast	*current;

	current = root;
	i = 0;
	print_node(current);
	if (current->left)
	{
		printf(BLUE "left_%s:\n" RST, current->args[0]);
		print_ast(current->left, level + 1);
	}
	if (current->right)
	{
		printf(BLUE "right_%s:\n" RST, current->args[0]);
		print_ast(current->right, level + 1);
	}
}

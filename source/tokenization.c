/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaferna2 <jaferna2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 17:44:52 by jaferna2          #+#    #+#             */
/*   Updated: 2025/02/25 17:16:23 by jaferna2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/* TO DO TOkenization with scheme: 
		 	[ROOT]					
                │  					
       ┌────────┴────────┐  			
       │                 │  			
   [Logical Op]      [Sequence (;)]  	
       │                 │  			
   ┌───┴───┐         ┌───┴───┐  		
   [Pipe (|)]    [Redirections (>, <)]
       │                 │  			
   ┌───┴───┐         ┌───┴───┐  		
   [Command]      [File / Argument]  	

*/

t_node_type	get_token_type(char	*token)
{
	if (ft_strncmp(token, "|", ft_strlen(token)) == 0)
		return (NODE_PIPE);
	else if (ft_strncmp(token, "<<", ft_strlen(token) == 0))
		return (NODE_HEREDOC);
	else if (ft_strncmp(token, "<", ft_strlen(token)) == 0)
		return (NODE_REDIR_IN);
	else if (ft_strncmp(token, ">", ft_strlen(token)) == 0)
		return (NODE_REDIR_OUT);
	else if (ft_strncmp(token, ">>", ft_strlen(token)) == 0)
		return (NODE_REDIR_APPEND);
	else
		return (NODE_CMD);
}
// 1º Creación Nodo
// 2º Sincronización / validación root
// 3º Enganchar left / right
t_ast	*create_ast(char **tokens)
{
	t_ast		*root;
	t_ast		*new_node;
	t_ast		*current;
	t_node_type	type;
	int			i;

	root = NULL;
	i = 0;
	while (tokens[i])
	{
		type = get_token_type(tokens[i]);
		if (type == NODE_CMD)
		{
			new_node = create_node(&tokens[i], i);
			// if (!root)
			// 	root = new_node;
			// else if (current && current->type != NODE_CMD)
			// 	current->right = new_node;
			// current = new_node;
		}
		else if (type == NODE_PIPE)
		{
			new_node = create_node(&tokens[i], &i);
			// new_node->left = root;
			// root = new_node;
			// current = new_node;
		}
		else if (type == NODE_REDIR_OUT || type == NODE_REDIR_APPEND)
		{
			new_node = create_node(&tokens[i], &i);
			// if (current)
			// 	current->right = new_node;
			// i++;
		}
		i++;
	}
	return (root);
}

t_ast	*create_node(char **args, int *indx)
{
	t_ast	*node;
	int		i;

	i = &indx;
	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = get_token_type(args[0]);
	while (args[i] && get_token_type(args[i]) != NODE_CMD)
		i++;
	node->args = malloc(sizeof(char *) * (i + 1));
	if (!node->args)
	{
		free(node);
		return (NULL);
	}
	while (args[*indx])
	{
		node->args[*indx] = ft_strdup(args[*indx]);
		*indx++;
	}
	node->args[i] = NULL;
	node->right = NULL;
	node->left = NULL;
	node->root = NULL;
	return (node);
}

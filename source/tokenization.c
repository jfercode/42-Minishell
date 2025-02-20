/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaferna2 <jaferna2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 17:44:52 by jaferna2          #+#    #+#             */
/*   Updated: 2025/02/20 18:56:40 by jaferna2         ###   ########.fr       */
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

static t_type	get_token_type(char	*token)
{
	if (ft_strncmp(token, "|", ft_strlen(token)) == 0)
		return (PIPE);
	else if (ft_strncmp(token, "<", ft_strlen(token)) == 0)
		return (REDIR_IN);
	else if (ft_strncmp(token, ">", ft_strlen(token)) == 0)
		return (REDIR_OUT);
	else if (ft_strncmp(token, "<", ft_strlen(token)) == 0)
		return (REDIR_IN);
	else return (CMD);	
}

/*	To do: NECESITO MOVERME EN LA LISTA ENLAZADA PARA 
ASIGNAR LOS VALORES DEL AST */
t_ast	*create_ast(char **tokenizated_line)
{
	t_ast	*current;
	t_ast	*left;

	current = *tokenizated_line;
	left = NULL;
	while (current)
	{
		// CREACIÓN DE NODOS Y RAMAS DEL AST
	}
}

t_ast	*create_node(t_type node_type, char **args,
			t_ast *left, t_ast *right)
{
	t_ast	*node;
	
	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = get_token_type(args);
	node->node = args;
	node->left = left;
	node->rigth = right;
	return (node);
}

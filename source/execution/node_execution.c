/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaferna2 <jaferna2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:41:17 by jaferna2          #+#    #+#             */
/*   Updated: 2025/03/17 18:11:09 by jaferna2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * 	type: CMD
 *	token: echo
 * 	token arg[0]: echo
 *	token arg[1]: hello world
 */
void	execute_cmd_node(t_ast *node)
{
	// Execute cmd simple 
}
/**
 *	type: PIPE
 *	token: |
 *	left: x
 *	right: y
 */
void	execute_pipe_node(t_ast *node)
{
	// call pipe_function(x, y)
}

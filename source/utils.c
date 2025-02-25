/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaferna2 <jaferna2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 17:52:44 by jaferna2          #+#    #+#             */
/*   Updated: 2025/02/25 16:30:55 by jaferna2         ###   ########.fr       */
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaferna2 <jaferna2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 15:35:43 by jaferna2          #+#    #+#             */
/*   Updated: 2025/03/17 18:48:08 by jaferna2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool		g_running = true;

static void	ft_start_gigachell(void)
{
	ft_signal(SIGINT, ft_handle_sigint, false);
	ft_signal(SIGTERM, ft_handle_sigterm, false);
	ft_signal(SIGQUIT, SIG_IGN, false);
}

static void	ft_exec_line(char *line)
{
	char	**mtx;

	add_history(line);
	if (syntax_error(line) == ERROR)
		free(line);
	else
	{
		mtx = create_matrix(line);
		print_matrix(mtx);
		t_ast *ast = create_ast(mtx);
		if(!ast)
			ft_error_exit("Error creating AST\n");
		ft_printf(STDOUT_FILENO, "AST_DEEP: %d\n", obtain_ast_deep(ast));
		print_ast(ast, 0); // TO DO -> DELETE PRINT_AST -> EXECUTE AST HERE
		free_ast(ast);
		free_matrix(mtx);
	}
}
 
/**
 * Main function of the program
 */
int	main(void)
{
	char	*line;

	ft_start_gigachell();
	while (g_running)
	{
		line = readline(GREEN"Gigachell> "RST);
		if (!line)
			break;
		else if (*line)
			ft_exec_line(line);
		free (line);
	}
	printf("Leaving Gigachell...\n");
	rl_clear_history();
	return (EXIT_SUCCESS);
}

// static void	reorder_matrix(char **tokens)
// {
// 	int i = 0, j, k;
//     while (tokens[i])
//     {
// 		ft_printf(1, GREEN"Reordered matrix:"RST"\n");
// 		print_matrix(tokens);
//         // Si encontramos un comando (CMD)
//         if (get_token_type(tokens[i]) == NODE_CMD)
//         {
//             j = i + 1; // Buscar redirecciones después del comando
//             while (tokens[j] && get_token_type(tokens[j]) != NODE_PIPE)
//             {
//                 // Si encontramos una redirección
//                 if (get_token_type(tokens[j]) == NODE_REDIR_IN ||
//                     get_token_type(tokens[j]) == NODE_REDIR_OUT ||
//                     get_token_type(tokens[j]) == NODE_HEREDOC ||
//                     get_token_type(tokens[j]) == NODE_REDIR_APPEND)
//                 {
//                     // La redirección y su argumento deben moverse al final del bloque del comando
//                     char *redir = tokens[j];
//                     char *file = tokens[j + 1];

//                     // Desplazar los elementos para hacer espacio
//                     k = j;
//                     while (tokens[k + 2])
//                     {
//                         tokens[k] = tokens[k + 2];
//                         k++;
//                     }
//                     tokens[k] = redir;
//                     tokens[k + 1] = file;
//                     tokens[k + 2] = NULL; // Asegurar fin de la matriz
//                     j = i; // Reiniciar `j` para revisar desde la nueva posición de `i`
//                 }
//                 j++;
//             }
//         }
//         i++;
//     }
// }

// /**
//  * AST main de pruebas
//  */
// int	main(void)
// {
// 	char	*mtx[] = {"grep", "<<", "in", "a", "|", "echo" ,"Hello World" ,">" ,"out", NULL};
// 	ft_printf(1, GREEN"Original matrix:"RST"\n");
// 	print_matrix(mtx);
// 	// reorder_matrix(mtx);
// 	// ft_printf(1, GREEN"Reordered matrix:"RST"\n");
// 	// print_matrix(mtx);
// 	// t_ast *ast = create_ast(mtx);
// 	// if (!ast)
// 	// 	ft_error_exit("Error creating AST\n");
// 	// print_ast(ast, 0);
// 	// free_ast(ast);
// 	return (EXIT_SUCCESS);
// }

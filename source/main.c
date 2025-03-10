/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaferna2 <jaferna2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 15:35:43 by jaferna2          #+#    #+#             */
/*   Updated: 2025/03/10 17:00:11 by jaferna2         ###   ########.fr       */
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

// LINE IS GOING TO BE OUR TEXT TO TOKENIZE
// int	main(void)
// {
// 	char	*line;

// 	ft_start_gigachell();
// while (g_running)
// 	{
// 		line = readline(GREEN"Gigachell> "RST);
// 		if (!line)
// 			break;
// 		else if (*line)
// 		{
// 			add_history(line);
// 			syntax_error(line);
// 			char	**mtx = create_matrix(line);
// 			for (int i = 0; mtx[i]; i++)
// 				printf("matrix[%d]: %s\n", i, mtx[i]);
// 			t_ast *ast = create_ast(mtx);
// 			if(!ast)
// 				// ERROR
// 			print_ast(ast, 0);
// 		}	
// 		free (line);	
// 	}
// 	printf("Leaving Gigachell...\n");
// 	rl_clear_history();
// 	return (EXIT_SUCCESS);
// }

/*
	
	pruebas a realizar:
	1-	cat << EOF > file.txt | Here doc + redireccion > CORRECTO

	2-	cat << EOF | wc -l 

	3-	grep "hello" < file.txt << EOF

	4-	cat file.txt | grep "hello" | wc -l > result.txt

	5-	echo "Start" >> log.txt && cat << EOF >> log.txt

*/
// // -> MAIN TO TEST TOKENIZATION
int	main (void)
{
	char *tokens[] = {"grep", "hello", "<", "file.txt", "<<", "EOF", NULL};
	t_ast *ast = create_ast(tokens);
	print_ast (ast, 0);
	return(EXIT_SUCCESS);
}

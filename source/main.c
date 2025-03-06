/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaferna2 <jaferna2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 15:35:43 by jaferna2          #+#    #+#             */
/*   Updated: 2025/03/06 18:37:11 by jaferna2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	g_running = true;

static void	ft_start_gigachell()
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
// 	while (g_running)
// 	{
// 		line = readline(GREEN"Gigachell> "RST);
// 		if (!line)
// 			break;
// 		else if (*line)
// 			add_history(line);
// 		free (line);
// 	}
// 	printf("Leaving Gigachell...\n");
// 	rl_clear_history();
// 	return (EXIT_SUCCESS);
// }

/*	
	pruebas a realizar:
	1-	cat << EOF > file.txt | OKEY

	2-	cat << EOF | wc -l OKEY

	3-	grep "hello" < file.txt << EOF OKEY

	4-	cat file.txt | grep "hello" | wc -l > result.txt OKEY

	5-	echo "Start" >> log.txt && cat << EOF >> log.txt   ¿LOGICAL OP?

*/
// // -> MAIN TO TEST TOKENIZATION
int	main (void)
{	
	char *tokens[] = {"grep", "<<", "test", "t", "|", "cat", "<<", "hola", NULL};
	t_ast *ast = create_ast(tokens);
	print_ast (ast, 0);
	return(EXIT_SUCCESS);
}

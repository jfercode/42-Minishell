/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penpalac <penpalac@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 15:35:43 by jaferna2          #+#    #+#             */
/*   Updated: 2025/02/20 19:07:14 by penpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool		g_running = true;
void		error(char *line);

static void	ft_start_gigachell(void)
{
	ft_signal(SIGINT, ft_handle_sigint, false);
	ft_signal(SIGTERM, ft_handle_sigterm, false);
	ft_signal(SIGQUIT, SIG_IGN, false);
}

// LINE IS GOING TO BE OUR TEXT TO TOKENIZE
int	main(void)
{
	char	*line;

	while (g_running)
	{
		line = readline(GREEN "Gigachell> " RST);
		if (!line)
		{
			printf("Leaving Gigachell...\n");
			break ;
		}
		else if (*line)
			add_history(line);
		error(line);
		free(line);
	}
	rl_clear_history();
	return (0);
}

// typedef struct s_lst
// {
// 	char	*type;
// 	char	*value;
// 	t_lst	*next;
// }	t_lst;

// void error(char *line)
// {
// 	t_lst *list;
// 	list = malloc(sizeof(t_list));
// 	char **matrix = ft_split(line, ' ');
// 	int i = 0;
// 	while(matrix[i])
// 	{
// 		list->value = matrix[i];
// 		list->next = NULL;


// 		i++;
// 		list = list->next;
// 	}
// }

// else
// {
// 	while (end + 1 > start)
// 	{
// 		matrix[start] = ft_strjoin(matrix[start], " ");
// 		matrix[start] = ft_strjoin(matrix[start], matrix[start + 1]);
// 		matrix[start + 1] = matrix[start + 1 + j];
// 		end--;
// 		j++;
// 	}
// 	i = 0;
// 	while (matrix[i])
// 	{
// 		matrix[start + 1] = matrix[start + 1 + i];
// 		i++;
// 	}
// }

// void	error(char *line)
// {
// 	char	**matrix;
// 	char	**matwo;
// 	int		i;
// 	int		quote;
// 	int		start;
// 	int		end;
// 	int		j;

// 	matrix = ft_split(line, ' ');
// 	i = 0;
// 	quote = 0;
// 	start = 0;
// 	end = 0;
// 	while (matrix[i])
// 	{
// 		if (matrix[i][0] == '"' || matrix[i][0] == "'")
// 		{
// 			quote++;
// 			start = i;
// 		}
// 		if (matrix[i][ft_strlen(matrix[i]) - 1] == '"' \
// 			|| matrix[i][ft_strlen(matrix[i]) - 1] == "'")
// 		{
// 			quote++;
// 			end = i;
// 		}
// 		i++;
// 	}
// 	matwo = malloc(i + 1);
// 	j = 0;
// 	if (quote % 2 != 0)
// 	{
// 		printf(":/");
// 		exit(1);
// 	}
// 	else
// 	{
// 		i = 0;
// 		j = 0;
// 		while (matrix[j])
// 		{
// 			printf("i: %d, j: %d\n", i, j);
// 			if (i == start)
// 			{
// 				while (start < end) // could be an ft_strint
// 				{
// 					//ambas asignaciones fallan, crean segfault
// 					matwo[i] = ft_strjoin(matrix[j], ' ');
// 					matwo[i] = ft_strjoin(matwo[i], matrix[j]);
// 					start++;
// 					j++;
// 				}
// 			}
// 			matwo[i] = matrix[j];
// 			i++;
// 			j++;
// 		}
// 	}
// 	i = 0;
// 	while (matwo[i])
// 	{
// 		printf("line %d: %s\n", i, matwo[i]);
// 		i++;
// 	}
// }

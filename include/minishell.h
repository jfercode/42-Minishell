/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaferna2 <jaferna2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 09:56:46 by jaferna2          #+#    #+#             */
/*   Updated: 2025/02/20 18:51:10 by jaferna2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <dirent.h>
# include <sys/stat.h>
# include <string.h>
# include <errno.h>
# include <termios.h>
# include <term.h>
# include <sys/ioctl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../source/libft/include/libft.h"

# define RST	"\033[0m"
# define RED	"\033[1;31m"
# define BLUE	"\033[1;34m"
# define GREEN	"\033[1;32m"

extern bool	g_running;

/* NODE TYPE ENUM*/
typedef enum e_type
{
	ARG,
	FILE_NAME,
	CMD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
}	t_type;

/* ABSTRACT SYNTAX TREE STRUCT*/
typedef struct s_ast
{
	t_type			type;
	char			**node;
	struct s_ast	*left;
	struct s_sat	*rigth;
}	t_ast;

/*SIGNALS BEHAVIOUR*/
void	ft_handle_sigint(int sig);
void	ft_handle_sigterm(int sig);
void	ft_handle_sigquit(int sig);
void	ft_signal(int signo, void *handler, bool use_siginfo);

/*ERROR HANDLING*/
void	ft_error_exit(const char *error_msg);

/* TOKENIZATION */
t_ast	*create_ast(char **line);
t_ast	*create_node(t_type node_type, char **args,
			t_ast *left, t_ast *right);

/* PARSE INPUT */
int	parsing_line(char *line);

#endif /*MINISHELL_H*/
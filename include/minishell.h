/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaferna2 <jaferna2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 09:56:46 by jaferna2          #+#    #+#             */
/*   Updated: 2025/03/03 18:00:29 by jaferna2         ###   ########.fr       */
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
	NODE_CMD,
	NODE_PIPE,
	NODE_HEREDOC,
	NODE_REDIR_IN,
	NODE_REDIR_OUT,
	NODE_REDIR_APPEND,
	// NODE_LOGICAL_OP
}	t_node_type;

/* ABSTRACT SYNTAX TREE STRUCT*/
typedef struct s_ast
{
	t_node_type		type;
	char			**args;
	struct s_ast	*left;
	struct s_ast	*right;
}					t_ast;

/*SIGNALS BEHAVIOUR*/
void		ft_handle_sigint(int sig);
void		ft_handle_sigterm(int sig);
void		ft_handle_sigquit(int sig);
void		ft_signal(int signo, void *handler, bool use_siginfo);

/*ERROR HANDLING*/
void		ft_error_exit(const char *error_msg);

/*HEREDOC HANDLING*/
int			ft_handle_here_doc(char *delimiter);

/* TOKENIZATION */
t_ast		*create_ast(char **line);
t_ast		*create_node(char **args, int *indx);

t_node_type	get_token_type(char	*token);

/* PARSE INPUT */
int			parsing_line(char *line);

/*	UTILS	*/
void		print_node(t_ast *node);
void		print_ast(t_ast *root, int level);

#endif /*MINISHELL_H*/

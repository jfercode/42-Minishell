/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penpalac <penpalac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 09:56:46 by jaferna2          #+#    #+#             */
/*   Updated: 2025/04/09 18:32:37 by penpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../source/libft/include/libft.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <term.h>
# include <termios.h>
# include <unistd.h>

# define RST "\033[0m"
# define RED "\033[1;31m"
# define BLUE "\033[1;34m"
# define GREEN "\033[1;32m"

# define ERROR -1

/* NODE TYPE ENUM	*/
typedef enum e_type
{
	NODE_CMD,
	NODE_PIPE,
	NODE_HEREDOC,
	NODE_REDIR_IN,
	NODE_REDIR_OUT,
	NODE_REDIR_APPEND,
	// NODE_LOGICAL_OP
}					t_node_type;

typedef struct s_data
{
	int		exit_status;
}					t_data;

/*	ABSTRACT SYNTAX TREE STRUCT	*/
typedef struct s_ast
{
	t_node_type		type;
	char			**args;
	char			**envp;
	pid_t			pid;
	int				fd_infile;
	int				fd_outfile;
	struct s_data	data;
	struct s_ast	*left;
	struct s_ast	*right;
}					t_ast;

/*	SIGNALS BEHAVIOUR	*/
void				ft_handle_sigint(int sig);
void				ft_handle_sigint_child(int sig);
void				ft_signal(int signo, void *handler, bool use_siginfo);

/*	ERROR HANDLING	*/
void				ft_error(const char *error_msg);
void				ft_error_exit(const char *error_msg);

/*	HEREDOC HANDLING	*/
int					ft_handle_here_doc(char *delimiter);

/* TOKENIZATION */
void				free_ast(t_ast *root);
void				free_node(t_ast *node);

t_ast				*create_ast(char **line, char **envp);
t_ast				*create_node(char **args, char **envp, int *indx);

t_node_type			get_token_type(char *token);

/*	EXECUTION	*/
int				execute_ast(t_ast *ast);

/*	NODE_EXECUTION	*/
void				run_command(t_ast *node);
void				execute_cmd_node(t_ast *node);
void				execute_pipe_node(t_ast *node);

/*	NODE_REDIRECTION	*/
int				execute_redirection_node(t_ast *node, int *fd_infile,
						int *fd_outfile, int *fd);
int					execute_heredoc_node(t_ast *node, int *fd_heredoc, int *n);
int					execute_redir_in_node(t_ast *node, int *fd_infile, int *n);
int					execute_redir_out_node(t_ast *node, int *fd_outfile, int *n);
int					execute_redir_append_node(t_ast *node, int *fd_outfile, int *n);

/*	PARSE INPUT	*/
int					syntax_error(char *line);
int					open_quotes(char *line);
int					invalid_op(char *line);
int					invalid_env(char *line);
int					invalid_redir(char *line);
char				**expand_matrix(char **matrix, char **envp, t_data *data);

/*BUILTINS*/
void				ft_env(void);
void				ft_exit(void);
void				ft_export(char **args);
void				ft_unset(const char *var);

int					pwd(void);
int					cd(char *path);
int					ft_echo(int ar, char **args);

/*	UTILS	*/
void				print_node(t_ast *node);
void				print_matrix(char **matrix);
void				print_ast(t_ast *root, int level);
void				ft_read_fd(int fd);
void				ft_read_fd_name(char *filename);

/*	MATRIX HANDLING	*/
void				free_matrix(char **matrix);

void				split_line(char **matrix, char *line);
char				**create_matrix(char *line, char **envp, t_data *data);
char				**handle_meta(char **matrix);

#endif /*	MINISHELL_H	*/

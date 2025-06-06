/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaferna2 < jaferna2@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 09:56:46 by jaferna2          #+#    #+#             */
/*   Updated: 2025/05/01 17:09:45 by jaferna2         ###   ########.fr       */
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
	int				exit_status;
	int				exit;
	char			**envp;
}					t_data;

/*	ABSTRACT SYNTAX TREE STRUCT	*/
typedef struct s_ast
{
	t_node_type		type;
	char			**args;
	pid_t			pid;
	int				fd_infile;
	int				fd_outfile;
	struct s_data	*data;
	int				exit_status;
	struct s_ast	*left;
	struct s_ast	*right;
}					t_ast;

/*	SIGNALS BEHAVIOUR	*/
void				ft_handle_sigint_bloq(int sig);
void				ft_handle_sigint_here(int sig);
void				ft_handle_sigint_pipes(int sig);
void				ft_handle_sigint_normal(int sig);
void				ft_signal(int signo, void *handler, bool use_siginfo);

/*	ERROR HANDLING	*/
void				ft_error(const char *error_msg);
void				ft_error_exit(const char *error_msg);

/*	HEREDOC HANDLING	*/
int					ft_handle_here_doc(char *delimiter);

/*	PARSE INPUT	*/
void				free_matrix(char **matrix);
void				omit_spaces(char *line, int *i);

int					syntax_error(char *line);
int					open_quotes(char *line);
int					invalid_op(char *line);
int					invalid_env(char *line);
int					invalid_redir(char *line);

char				**cleanup_matrix(char **matrix);
char				**separate_tokens(char **matrix);
char				**split_line(char **matrix, char *line);
char				**create_matrix(char *line, t_data *data);
char				**expand_matrix(char **matrix, t_data *data);

/* TOKENIZATION */
void				free_ast(t_ast *root);
void				free_node(t_ast *node);
void				free_ast(t_ast *root);
void				free_node(t_ast *node);

t_ast				*create_ast(char **line, t_data *data);
t_ast				*create_node(char **args, t_data *data, int *indx);

t_node_type			get_token_type(char *token);
t_node_type			get_token_type(char *token);

/*	EXECUTION	*/
int					execute_ast(t_ast *ast);

/*	NODE_EXECUTION	*/
void				run_command(t_ast *node);
void				execute_cmd_node(t_ast *node);
void				execute_pipe_node(t_ast *node);
void				wait_for_children_node(t_data *data);
void				order_cmds(t_ast *node, t_ast **cmds);
void				setup_redirections(t_ast *node, int *fd_in, int *fd_out);

int					handle_cmd_node(t_ast *node);
int					handle_pipe_node(t_ast *node);
int					apply_and_recurse(t_ast *node, int *fd_in, int *fd_out);
int					handle_redir_node(t_ast *node, int *fd_in, int *fd_out);
int					execute_node(t_ast *node, int *fd_infile, int *fd_outfile);

/*	NODE_REDIRECTION	*/
int					execute_redirection_node(t_ast *node, int *fd_infile,
						int *fd_outfile, int *fd);
int					execute_heredoc_node(t_ast *node, int *fd_heredoc, int *n);
int					execute_redir_in_node(t_ast *node, int *fd_infile, int *n);
int					execute_redir_out_node(t_ast *node, int *fd_outfile,
						int *n);
int					execute_redir_append_node(t_ast *node, int *fd_outfile,
						int *n);

/*BUILTINS*/
int					is_builtin(t_ast *node);
int					exec_builtin(t_ast *node);
int					ft_cd(char *path);
int					ft_exit(t_ast *ast);
int					ft_echo(int ar, char **args);
int					ft_env(t_ast *node);
int					ft_export(t_ast *node);
int					ft_pwd(void);
int					ft_unset(char **envp, const char *var);

/*	UTILS	*/
void				copy_envp(t_data *data, char **envp);
void				print_node(t_ast *node);
void				print_matrix(char **matrix);
void				print_ast(t_ast *root, int level);
void				free_data(t_data *data);
void				ft_start_gigachell(void);
char				*process_exit_value(int exit, char *line, int *index);
char				**process_dollar(char **matrix, t_data *data, int i,
						int *j);
char				*ft_prompt_readline(void);
int					check_ch(char c, int ch);

#endif /*	MINISHELL_H	*/

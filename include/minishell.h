/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penpalac <penpalac@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 09:56:46 by jaferna2          #+#    #+#             */
/*   Updated: 2025/02/26 18:30:31 by penpalac         ###   ########.fr       */
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

extern bool		g_running;

/*SIGNALS BEHAVIOUR*/
void			ft_handle_sigint(int sig);
void			ft_handle_sigterm(int sig);
void			ft_handle_sigquit(int sig);
void			ft_signal(int signo, void *handler, bool use_siginfo);

/*ERROR HANDLING*/
void			ft_error_exit(const char *error_msg);

int				syntax_error(char *line);
int				open_quotes(char *line);
int				invalid_redir(char *line);
int				invalid_op(char *line);
int				special_chars(char *line);

/*MATRIX HANDLING*/
int				read_until(char *line, int i, char quote);
int				omit_spaces(char *line, int i);
char			**split_line(char **matrix, char *line);
char			**create_matrix(char *line);
char			**handle_meta(char **matrix);

#endif /*MINISHELL_H*/
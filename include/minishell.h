/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaferna2 <jaferna2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 09:56:46 by jaferna2          #+#    #+#             */
/*   Updated: 2025/02/12 11:15:08 by jaferna2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>       		// printf, perror
#include <stdlib.h>      		// malloc, free, getenv, exit
#include <unistd.h>      		// write, fork, read, dup, execve, isatty
#include <fcntl.h>       		// open, fcntl
#include <sys/wait.h>    		// wait, waitpid
#include <signal.h>      		// signal, sigaction, kill
#include <dirent.h>      		// opendir, readdir, closedir
#include <sys/stat.h>    		// stat, lstat, fstat
#include <string.h>      		// strerror
#include <errno.h>       		// errno
#include <termios.h>     		// tcsetattr, tcgetattr
#include <term.h>        		// tgetent, tputs
#include <sys/ioctl.h>   		// ioctl
#include <readline/readline.h>  // readline
#include <readline/history.h>   // add_history

#include "../source/libft/include/libft.h"

#endif
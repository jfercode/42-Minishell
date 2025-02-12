/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaferna2 <jaferna2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 10:19:42 by jaferna2          #+#    #+#             */
/*   Updated: 2025/02/12 12:48:32 by jaferna2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../include/minishell.h"
// #include <stdio.h>       		// printf, perror
// #include <stdlib.h>      		// malloc, free, getenv, exit
// #include <unistd.h>      		// write, fork, read, dup, execve, isatty
// #include <fcntl.h>       		// open, fcntl
// #include <sys/wait.h>    		// wait, waitpid
// #include <signal.h>      		// signal, sigaction, kill
// #include <dirent.h>      		// opendir, readdir, closedir
// #include <sys/stat.h>    		// stat, lstat, fstat
// #include <string.h>      		// strerror
// #include <errno.h>       		// errno
// #include <termios.h>     		// tcsetattr, tcgetattr
// #include <term.h>        		// tgetent, tputs
// #include <sys/ioctl.h>   		// ioctl
// #include <readline/readline.h>  // readline
// #include <readline/history.h>   // add_history

// int	main(void)
// {
	// char	*line;

	// line = readline("Input: ");
	// if (!line)
	// {
		// write(STDERR_FILENO, "Error: failed to read the line.\n", 34);
		// exit(EXIT_FAILURE);
	// }
	// if (*line != '\0')
		// add_history(line);
	// printf("Input readed: %s\nNew input: ", line);
	// rl_replace_line(readline(""), 0);
	// rl_on_new_line();
	// rl_redisplay();
	// rl_clear_history();
	// free(line);
	// return (0);
// }

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h> 
#include <signal.h>

int main() 
{
    pid_t pid;

	pid = fork();
	if (pid == -1)
	{
		perror("Error: Falied in fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		printf("Children process (PID: %d)\n", getpid());
		while (1)
			sleep(1);
	}
	else
	{
		printf("Parent process(PID: %d)\n", getpid());
		sleep(2);
		printf("Parent sendig SIGKILL to children.\n");
		kill(pid, SIGKILL);
		printf("Children process finished\n");
	}
	return (0);
}

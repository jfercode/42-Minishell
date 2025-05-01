/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handling.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaferna2 < jaferna2@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 17:44:19 by jaferna2          #+#    #+#             */
/*   Updated: 2025/05/01 12:40:46 by jaferna2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Removes the trailing newline character from a string.
 *
 * If the string is non-null and ends with a newline ('\n'),
 * this function replaces it with a null terminator.
 *
 * @param line The string to process.
 * @return The modified string without a trailing newline,
 * @return The modified string without a trailing newline,
 * or NULL if the input is NULL.
 */
static char	*remove_newline(char *line)
{
	size_t	len;
	char	*tmp;

	tmp = ft_strdup(line);
	free(line);
	len = ft_strlen(tmp);
	if (!len)
		return (NULL);
	if (len > 0 && tmp[len - 1] == '\n')
		tmp[len - 1] = '\0';
	return (tmp);
}

/**
 * @brief Child process: reads from stdin and writes lines to 
 * the heredoc file.
 *
 * Reads lines from standard input, compares each line to 
 * the delimiter, and writes them to a temporary file if they
 * don’t match. Stops when the delimiter is matched.
 * Also sets a custom SIGINT handler for the child process.
 *
 * @param tmp_fd File descriptor for the temporary heredoc file.
 * @param delimiter The end delimiter for the heredoc input.
 */
static void	ft_handle_here_doc_child(int tmp_fd, char *delimiter)
{
	char	*line;

	signal(SIGINT, ft_handle_sigint_here);
	while (1)
	{
		write(STDOUT_FILENO, "> ", 2);
		line = ft_get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		line = remove_newline(line);
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1) == 0)
		{
			free(line);
			break ;
		}
		write(tmp_fd, line, ft_strlen(line));
		write(tmp_fd, "\n", 1);
		free(line);
	}
	close(tmp_fd);
	exit (EXIT_SUCCESS);
}

/**
 * @brief Parent process: waits for the child and handles SIGINT behavior.
 *
 * Temporarily ignores SIGINT, waits for the child to finish processing
 * the heredoc input, then restores the original SIGINT handler.
 *
 * @param pid Process ID of the child.
 * @param tmp_fd File descriptor for the temporary heredoc file.
 * @return int Always returns EXIT_FAILURE, signaling heredoc end handling.
 */
static int	ft_handle_here_doc_parent(pid_t pid, int tmp_fd)
{
	int	status;

	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	signal(SIGINT, ft_handle_sigint_normal);
	close(tmp_fd);
	if (WIFSIGNALED(status))
		write (1, "\n", 1);
	return (EXIT_FAILURE);
}

/**
 * @brief Handles heredoc input by creating a temporary file and forking 
 * a process.
 *
 * Opens a temporary file and forks the process. The child process reads
 * from standard input until the given delimiter is found, writing each 
 * line into the file.
 * The parent waits for the child to finish and manages SIGINT handling.
 *
 * @param delimiter The string that marks the end of the heredoc input.
 * @return int Returns EXIT_FAILURE if an error occurs or the child is
 * interrupted.
 */
int	ft_handle_here_doc(char *delimiter)
{
	int		tmp_fd;
	pid_t	pid;

	tmp_fd = open("/tmp/heredoc_tmp.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (tmp_fd == -1)
		return (ft_error("Error: can't opening temp heredoc file"), 1);
	pid = fork();
	if (pid == 0)
		ft_handle_here_doc_child(tmp_fd, delimiter);
	else
		ft_handle_here_doc_parent(pid, tmp_fd);
	return (EXIT_FAILURE);
}

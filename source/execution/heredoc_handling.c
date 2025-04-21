/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handling.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaferna2 < jaferna2@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 17:44:19 by jaferna2          #+#    #+#             */
/*   Updated: 2025/04/21 18:45:05 by jaferna2         ###   ########.fr       */
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
 * @brief Processes here-document input.
 *
 * Opens a temporary file and repeatedly prompts the user with "heredoc> "
 *  to read input.
 * Each line (after removing its newline) is compared with the delimiter;
 *  if it matches, the file is closed and IS_HEREDOC is returned.
 *  if it matches, the file is closed and IS_HEREDOC is returned.
 * Otherwise, the line is written to the file.
 *
 * @param delimiter The string that terminates the here-document input.
 * 
 */
int	ft_handle_here_doc(char *delimiter)
{
	int		tmp_fd;
	char	*line;

	ft_printf(STDOUT_FILENO, "DELIMITER: %s\n", delimiter);
	tmp_fd = open("/tmp/heredoc_tmp.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (tmp_fd == -1)
		return (ft_error("Error: can't opening temp heredoc file"), 1);
	while (g_shell_mode == HEREDOC)
	{
		write(STDOUT_FILENO, "heredoc> ", 10);
		line = ft_get_next_line(STDIN_FILENO);
		if (!line || g_shell_mode != HEREDOC)
			break ;
		line = remove_newline(line);
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1) == 0)
			return (free(line), close(tmp_fd));
		write(tmp_fd, line, ft_strlen(line));
		write(tmp_fd, "\n", 1);
		free(line);
	}
	close(tmp_fd);
	if (g_shell_mode != HEREDOC)
		return (130);
	return (EXIT_FAILURE);
}

void	ft_read_fd_name(char *filename)
{
	int		i;
	int		tmp_fd;
	char	*line;

	tmp_fd = open(filename, O_RDONLY, 0644);
	if (!tmp_fd)
		return (ft_error("Error: can't read a fd"));
	line = ft_get_next_line(tmp_fd);
	if (!line)
		ft_error("Error: nothing to read");
	else
	{
		i = 0;
		while (line != NULL)
		{
			ft_printf(STDOUT_FILENO,
				GREEN"FD[%d]_ln[%d]: "RST"%s\n", tmp_fd, i, line);
			i++;
			free(line);
			line = ft_get_next_line(tmp_fd);
		}
	}
	close(tmp_fd);
}

void	ft_read_fd(int fd)
{
	int		i;
	char	*line;

	if (!fd)
		return (ft_error("Error: can't read a fd"));
	line = ft_get_next_line(fd);
	if (!line)
		ft_error("Error: nothing to read");
	else
	{
		i = 0;
		while (line != NULL)
		{
			ft_printf(STDOUT_FILENO,
				GREEN"FD[%d]_ln[%d]: "RST"%s\n", fd, i, line);
			i++;
			free(line);
			line = ft_get_next_line(fd);
		}
	}
	close(fd);
}

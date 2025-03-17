/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handling.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penpalac <penpalac@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 17:44:19 by jaferna2          #+#    #+#             */
/*   Updated: 2025/03/17 18:19:38 by penpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * @brief Removes the trailing newline character from a string.
 *
 * If the string is non-null and ends with a newline ('\n'),
 * this function replaces it with a null terminator.
 *
 * @param line The string to process.
 * @return The modified string without a trailing newline,
 * or NULL if the input is NULL.
 */
static char	*remove_newline(char *line)
{
	size_t	len;
	char	*tmp;

	if (!len)
		return (NULL);
	tmp = ft_strdup(line);
	free(line);
	len = ft_strlen(tmp);
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
 * Otherwise, the line is written to the file.
 *
 * @param delimiter The string that terminates the here-document input.
 * @return IS_HEREDOC when the delimiter is encountered,
	or 0 if an error occurs.
 */
int	ft_handle_here_doc(char *delimiter)
{
	int		tmp_fd;
	char	*line;

	tmp_fd = open("/tmp/heredoc_tmp.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (tmp_fd == -1)
		return (ft_error_exit("Error opening temp heredoc file"), EXIT_FAILURE);
	while (1)
	{
		write(STDOUT_FILENO, "heredoc> ", 10);
		line = ft_get_next_line(STDIN_FILENO);
			// EN DUDA CUANDO SE IMPLEMENTE VER QUE CARAJO PILLA
		if (!line)
			return (ft_error_exit("Error reading heredoc"), EXIT_FAILURE);
		line = remove_newline(line);
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1) == 0)
			return (free(line), close(tmp_fd), EXIT_FAILURE);
		write(tmp_fd, line, ft_strlen(line));
		write(tmp_fd, "\n", 1);
		free(line);
	}
	close(tmp_fd);
	return (EXIT_SUCCESS);
}

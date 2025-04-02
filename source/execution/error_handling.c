/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penpalac <penpalac@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 11:07:10 by jaferna2          #+#    #+#             */
/*   Updated: 2025/04/02 19:34:34 by penpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Prints an error message and terminates the program.
 *
 * This function prints the provided error message in red and
 * then exits the program with a failure status.
 *
 * @param error_msg A pointer to a null-terminated string containing
 * the error message to display.
 */
void	ft_error_exit(const char *error_msg)
{
	printf(RED "%s: "RST"%s\n", error_msg, strerror(errno));
	exit(EXIT_FAILURE);
}

/**
 * @brief Prints an error message.
 *
 * This function prints the provided error message in red.
 *
 * @param error_msg A pointer to a null-terminated string containing 
 * the error message to display.
 */
void	ft_error(const char *error_msg)
{
	printf(RED"%s: "RST"%s\n", error_msg, strerror(errno));
}

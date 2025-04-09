/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabalons <pabalons@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/04/09 17:56:13 by pabalons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/minishell.h"

/**
 * @brief Prints an error message and terminates the program.
 *
 * This function prints the provided error message in red and
 * This function prints the provided error message in red and
 * then exits the program with a failure status.
 *
 * @param error_msg A pointer to a null-terminated string containing
 * @param error_msg A pointer to a null-terminated string containing
 * the error message to display.
 */
void	ft_error_exit(const char *error_msg)
{
	printf("%s: %s\n", error_msg, strerror(errno));
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
	printf("%s: %s\n", error_msg, strerror(errno));
}

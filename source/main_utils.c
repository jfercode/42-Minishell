/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaferna2 < jaferna2@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 11:08:15 by jaferna2          #+#    #+#             */
/*   Updated: 2025/04/25 11:47:15 by jaferna2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_prompt_readline(void)
{
	char	*cwd;
	char	*temp;
	char	*path;
	char	*prompt;

	cwd = getcwd(NULL, 0);
	path = ft_strjoin(GREEN, cwd);
	temp = ft_strjoin(path, "/");
	prompt = ft_strjoin(temp, "Gigachell> " RST);
	free(path);
	free(temp);
	free(cwd);
	return (prompt);
}

void	ft_start_gigachell(void)
{
	struct sigaction	sa;

	signal(SIGINT, ft_handle_sigint_normal);
	signal(SIGTERM, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = ft_handle_sigint_normal;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		ft_error("Failed sigaction");
}

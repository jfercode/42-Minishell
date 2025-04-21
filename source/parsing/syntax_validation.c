/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_validation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaferna2 < jaferna2@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:43:06 by penpalac          #+#    #+#             */
/*   Updated: 2025/04/21 16:23:23 by jaferna2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// lo que dice bash en caso de error de direcciones es
// "syntax error near unexpected token"
// lo que dice bash en caso de error de direcciones es
// "syntax error near unexpected token"
// pero en los otros dos casos literalmente se vuelve un heardoc,
// esperando a que completes el comando
// asi que no dan un error,
// habría que salir directament o llamar a heredoc/crear nueva línea

int	syntax_error(char *line)
{
	if (open_quotes(line))
		return (ft_error("Syntax_error: unclosed quote\n"), ERROR);
	if (invalid_redir(line))
		return (ft_error("Syntax_error: near unexpected token\n"), ERROR);
	if (invalid_op(line))
		return (ft_error("Syntax_error: near unexpected token\n"), ERROR);
	if (invalid_env(line))
		return (ft_error("$: command not found\n"), ERROR);
	return (0);
}

int	open_quotes(char *line)
{
	char	quote_type;
	int		i;

	i = 0;
	quote_type = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			if (quote_type == line[i])
				quote_type = 0;
			else if (!quote_type)
				quote_type = line[i];
		}
		i++;
	}
	return (quote_type != 0);
}

int	invalid_redir(char *line)
{
	char	ch;
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '>' || line[i] == '<')
		{
			ch = line[i];
			i++;
			if (line[i] == ch)
				i++;
			while (line[i] && line[i] == ' ')
				i++;
			if (line[i] == '\0' || line[i] == '>' || line[i] == '<'
				|| line[i] == '|')
				return (1);
			return (0);
		}
		else
			i++;
	}
	return (0);
}

int	invalid_op(char *line)
{
	int	next_cmd;
	int	i;

	i = 0;
	next_cmd = 0;
	if (line[i] == '|' || line[i] == '&')
		return (1);
	while (line[i])
	{
		if (line[i] == '|')
		{
			if (next_cmd)
				return (1);
			next_cmd = 1;
		}
		else if (!(line[i] == ' '))
			next_cmd = 0;
		i++;
	}
	if (next_cmd)
		return (1);
	return (0);
}

int	invalid_env(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '$')
		{
			if (line[i - 1] != ' ' && line[i - 1] != '\"' && \
				line[i - 1] != '\0' && line[i - 1] != '\'')
				return (1);
			if (!ft_isalnum(line[i + 1]))
				return (1);
		}
		i++;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_validation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penpalac <penpalac@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:43:06 by penpalac          #+#    #+#             */
/*   Updated: 2025/02/21 17:04:17 by penpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// lo que dice bash en caso de error de direcciones es "syntax error near unexpected token"
// pero en los otros dos casos literalmente se vuelve un heardoc, 
// esperando a que completes el comando
// asi que no dan un error,
// habría que salir directament o llamar a heredoc/crear nueva línea

int	syntax_error(char *line)
{
	if (open_quotes(line))
	{
		printf("Error: unclosed quote\n");
		return (1);
	}
	if (invalid_redir(line))
	{
		printf("syntax error near unexpected token\n");
		return (1);
	}
	if (invalid_op(line))
	{
		printf("Error: invalid operation\n");
		return (1);
	}
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
	int		single_quotes;
	int		double_quotes;
	int		i;

	i = 0;
	single_quotes = 0;
	double_quotes = 0;
	while (line[i])
	{
		if (line[i] == 34)
			double_quotes++;
		else if (line[i] == 39)
			single_quotes++;
		if ((!(single_quotes % 2) && !(double_quotes % 2)) && (line[i] == '>'
				|| line[i] == '<'))
		{
			ch = line[i];
			i++;
			if (line[i] == ch) // si son dobles sigue
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

int	invalid_op(const char *line)
{
	int next_cmd;
	int single_quotes;
	int double_quotes;
	int i;

	i = 0;
	single_quotes = 0;
	double_quotes = 0;
	next_cmd = 0;
	if (line[i] == '|' || line[i] == '&')
		return (1);
	while (line[i])
	{
		if (line[i] == 34)
			double_quotes++;
		else if (line[i] == 39)
			single_quotes++;
		if (line[i] == '|' && !(single_quotes % 2) && !(double_quotes % 2))
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

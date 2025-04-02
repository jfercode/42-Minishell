/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaferna2 <jaferna2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:09:07 by jaferna2          #+#    #+#             */
/*   Updated: 2025/04/02 19:19:00 by jaferna2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ns;
	char	*aux;
	size_t	i;
	size_t	j;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		return (NULL);
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	ns = (char *) malloc((len + 1) * sizeof(char));
	if (!ns)
		return (NULL);
	aux = (char *)s;
	i = start;
	j = 0;
	while (aux[i] && j < len)
	{
		ns[j] = aux[i];
		i++;
		j++;
	}
	ns[j] = '\0';
	return (ns);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disilva <disilva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 18:44:17 by disilva           #+#    #+#             */
/*   Updated: 2024/03/15 22:45:13 by disilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stddef.h>

static	unsigned int	sizes_(char const *s)
{
	unsigned int		sizes;

	sizes = 0;
	while (s[sizes] != '\0')
		sizes++;
	return (sizes);
}

static	void	sub_fill(char const *s, unsigned int start,
				size_t len, char *sub)
{
	while (len > 0 && s[start] != '\0')
	{
		*sub = s[start];
		start++;
		sub++;
		len--;
	}
	*sub = '\0';
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char				*sub;
	unsigned int		sizes;

	sizes = sizes_(s);
	if (sizes <= start)
	{
		sub = malloc(1);
		if (sub == NULL)
			return (NULL);
		*sub = '\0';
		return (sub);
	}
	if ((sizes - start) > len)
		sub = (char *)malloc((len + 1) * sizeof(char));
	else
		sub = (char *)malloc((sizes - start + 1) * sizeof(char));
	if (sub == NULL)
		return (NULL);
	sub_fill(s, start, len, sub);
	return (sub);
}

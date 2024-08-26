/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disilva <disilva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 13:49:22 by disilva           #+#    #+#             */
/*   Updated: 2024/03/15 22:45:38 by disilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*ft_strchr(const char *s, int c)
{
	char	c2;

	c2 = (char)c;
	while (*s != '\0' && *(char *)s != c2)
	{
		s++;
	}
	if (c2 == *(char *)s)
		return ((char *)s);
	else
		return (NULL);
}

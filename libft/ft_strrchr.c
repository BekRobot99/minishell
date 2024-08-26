/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disilva <disilva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 13:59:38 by disilva           #+#    #+#             */
/*   Updated: 2024/03/15 22:45:55 by disilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strrchr(const char *s, int c)
{
	char	*s2;
	char	c2;

	s2 = (char *)s;
	c2 = (char)c;
	while (*s != '\0')
		s++;
	while (s != s2 && *s != c2)
	{
		s--;
	}
	if (c2 == *s)
		return ((char *)s);
	else
		return (NULL);
}

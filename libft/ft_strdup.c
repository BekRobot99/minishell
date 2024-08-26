/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disilva <disilva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 18:27:37 by disilva           #+#    #+#             */
/*   Updated: 2024/03/15 22:37:22 by disilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strdup(const char *s1)
{
	char	*s12;
	char	*s2;
	int		size;

	s12 = (char *)s1;
	size = 0;
	while (*s12 != '\0')
	{
		s12++;
		size++;
	}
	s2 = (char *)malloc((size + 1) * sizeof(char));
	if (s2 == NULL)
		return (NULL);
	s12 = s2;
	while (*s1 != '\0')
	{
		*s2 = *s1;
		s1++;
		s2++;
	}
	*s2 = '\0';
	return (s12);
}

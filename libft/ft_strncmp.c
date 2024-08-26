/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disilva <disilva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:07:14 by disilva           #+#    #+#             */
/*   Updated: 2024/03/15 22:38:45 by disilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	i = 1;
	while (*s1 == *s2 && i < n && *s1 != '\0')
	{
		s1++;
		s2++;
		i++;
	}
	i = *(unsigned char *)s1 - *(unsigned char *)s2;
	return ((int)i);
}

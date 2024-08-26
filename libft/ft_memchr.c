/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disilva <disilva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:44:04 by disilva           #+#    #+#             */
/*   Updated: 2024/03/15 22:35:30 by disilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	while (*(const unsigned char *)s != (unsigned char)c && n > 1)
	{
		s++;
		n--;
	}
	if (*(const unsigned char *)s == (unsigned char)c && n > 0)
		return ((void *)s);
	else
		return (NULL);
}

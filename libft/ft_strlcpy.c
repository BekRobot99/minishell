/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disilva <disilva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 21:00:30 by disilva           #+#    #+#             */
/*   Updated: 2024/03/15 22:38:33 by disilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	srcsize;
	char	*srccpy;

	srcsize = 0;
	srccpy = (char *)src;
	while (*srccpy != '\0')
	{
		srccpy++;
		srcsize++;
	}
	while (*src != '\0' && dstsize > 1)
	{
		*dst = *src;
		dst++;
		src++;
		dstsize--;
	}
	if (dstsize > 0)
		*dst = '\0';
	return (srcsize);
}

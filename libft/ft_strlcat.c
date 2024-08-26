/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disilva <disilva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 21:24:23 by disilva           #+#    #+#             */
/*   Updated: 2024/03/15 22:37:43 by disilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	catsize;

	catsize = 0;
	while (*dst != '\0' && dstsize > 0)
	{
		dst++;
		dstsize--;
		catsize++;
	}
	while (*src != '\0' && dstsize > 1)
	{
		*dst = *src;
		dst++;
		dstsize--;
		src++;
		catsize++;
	}
	while (*src != '\0')
	{
		catsize++;
		src++;
	}
	if (dstsize > 0)
		*dst = '\0';
	return (catsize);
}

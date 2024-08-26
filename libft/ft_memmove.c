/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disilva <disilva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 20:54:05 by disilva           #+#    #+#             */
/*   Updated: 2024/03/15 22:36:05 by disilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	void	*dst2;

	if (dst == NULL && src == NULL)
		return (NULL);
	dst2 = dst;
	if ((unsigned char *)dst < (unsigned char *)src)
	{
		while (len > 0)
		{
			*(unsigned char *)dst = *(unsigned char *)src;
			dst++;
			src++;
			len--;
		}
	}
	else
	{
		while (len > 0)
		{
			*(unsigned char *)(dst + len - 1)
				= *(unsigned char *)(src + len - 1);
			len--;
		}
	}
	return (dst2);
}

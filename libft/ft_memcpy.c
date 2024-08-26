/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disilva <disilva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 20:01:58 by disilva           #+#    #+#             */
/*   Updated: 2024/03/15 22:35:58 by disilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	void	*dst2;

	if (dst == NULL && src == NULL)
		return ((void *)src);
	dst2 = dst;
	while (n > 0)
	{
		*(unsigned char *)dst = *(unsigned char *)src;
		dst++;
		src++;
		n--;
	}
	return (dst2);
}

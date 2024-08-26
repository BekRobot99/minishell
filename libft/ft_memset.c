/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disilva <disilva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 19:06:01 by disilva           #+#    #+#             */
/*   Updated: 2024/03/15 22:36:07 by disilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memset(void *b, int c, size_t len)
{
	void	*a;

	a = b;
	while (len > 0)
	{
		*(unsigned char *)a = (unsigned char)c;
		a++;
		len--;
	}
	return (b);
}

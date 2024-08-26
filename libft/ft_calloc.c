/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disilva <disilva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 02:40:23 by disilva           #+#    #+#             */
/*   Updated: 2024/08/21 00:33:28 by disilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stddef.h>

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	n;
	size_t	i;

	n = count * size;
	ptr = malloc(n);
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (i < n)
	{
		((char *)ptr)[i] = '\0';
		i++;
	}
	return (ptr);
}

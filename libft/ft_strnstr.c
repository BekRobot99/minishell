/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disilva <disilva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:49:37 by disilva           #+#    #+#             */
/*   Updated: 2024/03/15 22:39:00 by disilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

static	char	*ft_strnstr_part2(const char *haystack,
					const char *needle, size_t len)
{
	int		i;
	char	*hayaddress;

	i = 0;
	while (*haystack != '\0' && len > 0 && needle[i] != '\0')
	{
		if (*haystack == needle[i])
		{
			if (i == 0)
				hayaddress = (char *)haystack;
			i++;
		}
		else if (*haystack != needle[i] && i != 0)
		{
			haystack = hayaddress;
			len = len + i;
			i = 0;
		}
		haystack++;
		len--;
	}
	if (needle[i] == '\0')
		return (hayaddress);
	return (NULL);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*hayaddress;

	hayaddress = (char *)haystack;
	if (*needle == '\0')
		return (hayaddress);
	hayaddress = ft_strnstr_part2(haystack, needle, len);
	return (hayaddress);
}

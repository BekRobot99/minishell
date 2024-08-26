/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disilva <disilva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 22:45:36 by disilva           #+#    #+#             */
/*   Updated: 2024/03/15 22:38:42 by disilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*new;

	i = 0;
	while (s[i] != '\0')
		i++;
	new = (char *)malloc((i + 1) * sizeof(char));
	if (new == NULL)
		return (NULL);
	new[i] = '\0';
	while (i > 0)
	{
		new[i - 1] = f(i - 1, s[i - 1]);
		i--;
	}
	return (new);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disilva <disilva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 18:58:38 by disilva           #+#    #+#             */
/*   Updated: 2024/03/15 22:37:29 by disilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static	void	concatuate(char const *s1, char const *s2, char *s3)
{
	while (*s1 != '\0')
	{
		*s3 = *s1;
		s1++;
		s3++;
	}
	while (*s2 != '\0')
	{
		*s3 = *s2;
		s2++;
		s3++;
	}
	*s3 = '\0';
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s3;
	int		sizes1;
	int		sizes2;
	char	*s1cpy;
	char	*s2cpy;

	sizes1 = 0;
	s1cpy = (char *)s1;
	while (*s1cpy != '\0')
	{
		s1cpy++;
		sizes1++;
	}
	sizes2 = 0;
	s2cpy = (char *)s2;
	while (*s2cpy != '\0')
	{
		s2cpy++;
		sizes2++;
	}
	s3 = (char *)malloc((sizes1 + sizes2 + 1) * sizeof(char));
	if (s3 == NULL)
		return (NULL);
	concatuate(s1, s2, s3);
	return (s3);
}

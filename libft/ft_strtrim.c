/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disilva <disilva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 19:17:33 by disilva           #+#    #+#             */
/*   Updated: 2024/03/15 23:25:14 by disilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static	int	ft_strtrimpart3(char const *s1, char const *set, int j, int k)
{
	int	i;

	while (j > k)
	{
		i = 0;
		while (set[i] != '\0')
		{
			if (set[i] == s1[j])
			{
				j--;
				break ;
			}
			i++;
		}
		if (set[i] == '\0')
			break ;
	}
	return (j);
}

static	char	*ft_strtrimpart2(char const *s1, char const *set, int j, int k)
{
	char	*s1cpy;
	int		i;

	while (s1[j] != '\0')
		j++;
	j--;
	j = ft_strtrimpart3(s1, set, j, k);
	s1cpy = (char *)malloc((j - k + 2) * sizeof(char));
	if (s1cpy == NULL)
		return (NULL);
	i = 0;
	while (k <= j)
	{
		s1cpy[i] = s1[k];
		i++;
		k++;
	}
	s1cpy[i] = '\0';
	return (s1cpy);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	int		k;
	char	*s1cpy;

	j = 0;
	while (s1[j] != '\0')
	{
		i = 0;
		while (set[i] != '\0')
		{
			if (set[i] == s1[j])
			{
				j++;
				break ;
			}
			i++;
		}
		if (set[i] == '\0')
			break ;
	}
	k = j;
	s1cpy = ft_strtrimpart2(s1, set, j, k);
	return (s1cpy);
}

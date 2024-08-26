/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disilva <disilva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 20:28:06 by disilva           #+#    #+#             */
/*   Updated: 2024/03/15 22:36:58 by disilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static	void	fillwords(char	**array, char const *s, char c)
{
	int		i;
	int		nwords;
	int		nletters;

	i = 0;
	nwords = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			nletters = 0;
			while (s[i] != c && s[i] != '\0')
			{
				array[nwords][nletters] = s[i];
				i++;
				nletters++;
			}
			array[nwords][nletters] = '\0';
			nwords++;
		}
		else
			i++;
	}
	array[nwords] = NULL;
}

static	char	**freee(char **array, int nwords)
{
	int	i;

	i = 0;
	while (i < nwords)
	{
		free(array[i]);
		i++;
	}
	free(array);
	return (NULL);
}

static	char	**createwords(char **array, const char *s, char c)
{
	int	i;
	int	nwords;
	int	nletters;

	i = 0;
	nwords = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			nletters = 0;
			while (s[i] != c && s[i] != '\0')
			{
				i++;
				nletters++;
			}
			array[nwords] = (char *)malloc((nletters + 1) * sizeof(char));
			if (array[nwords] == NULL)
				return (NULL);
			nwords++;
		}
		else
			i++;
	}
	return (array);
}

static	int	countwords(const char *s, char c)
{
	int		i;
	int		nwords;

	i = 0;
	nwords = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			nwords++;
			while (s[i] != c && s[i] != '\0')
				i++;
		}
		else
			i++;
	}
	return (nwords);
}

char	**ft_split(const char *s, char c)
{
	int		i;
	int		nwords;
	char	**array;

	nwords = countwords(s, c);
	array = (char **)malloc((nwords + 1) * sizeof(char *));
	if (array == NULL)
		return (NULL);
	i = 0;
	while (i <= nwords)
	{
		array[i] = NULL;
		i++;
	}
	if (createwords(array, s, c) == NULL)
		return (freee(array, nwords));
	fillwords(array, s, c);
	return (array);
}

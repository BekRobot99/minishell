/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disilva <disilva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 20:52:16 by disilva           #+#    #+#             */
/*   Updated: 2024/03/15 22:35:11 by disilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static	int	ft_ndigits(int n)
{
	int	ndigits;

	ndigits = 1;
	while (n > 9)
	{
		n = n / 10;
		ndigits++;
	}
	return (ndigits);
}

static	void	ft_itoapart2(char *num, int n, int ndigits, int negative)
{
	if (n == 0)
		num[0] = '0';
	num[ndigits + negative] = '\0';
	while (n > 0)
	{
		ndigits--;
		num[ndigits + negative] = n % 10 + '0';
		n = n / 10;
	}
	if (negative == 1)
		num[0] = '-';
}

char	*ft_itoa(int n)
{
	int		ndigits;
	char	*num;
	int		large;
	int		negative;

	large = 0;
	if (n == -2147483648)
		large = 1;
	if (n == -2147483648)
		n++;
	negative = 0;
	if (n < 0)
		negative = 1;
	if (n < 0)
		n = -n;
	ndigits = ft_ndigits(n);
	num = (char *)malloc((ndigits + 1 + negative) * sizeof(char));
	if (num == NULL)
		return (NULL);
	ft_itoapart2(num, n, ndigits, negative);
	if (large == 1)
		num[10] = '8';
	return (num);
}

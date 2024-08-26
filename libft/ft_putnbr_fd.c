/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disilva <disilva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 00:21:02 by disilva           #+#    #+#             */
/*   Updated: 2024/03/15 22:36:19 by disilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putnbr_fd(int n, int fd)
{
	char	num;
	int		ncpy;
	long	digits;

	if (n == -2147483648)
		write (fd, "-2147483648", 11);
	if (n == 0)
		write (fd, "0", 1);
	if (n < 0 && n != -2147483648)
	{
		write (fd, "-", 1);
		n = -n;
	}
	ncpy = 0;
	digits = 1;
	while (ncpy != n && n != -2147483648)
	{
		ncpy = n;
		while (ncpy >= 10 * digits)
			ncpy = ncpy / 10;
		num = ncpy % 10 + '0';
		write (fd, &num, 1);
		digits = digits * 10;
	}
}

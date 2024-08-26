/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disilva <disilva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 16:24:17 by disilva           #+#    #+#             */
/*   Updated: 2024/03/15 22:34:24 by disilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	int	i;
	int	negative;

	negative = 1;
	while ((*str > 8 && *str < 14) || *str == 32)
		str++;
	if (*str == '-')
	{
		negative = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	i = 0;
	while (*str > 47 && *str < 58)
	{
		i = i * 10 + (*str - 48);
		str++;
	}
	return (negative * i);
}

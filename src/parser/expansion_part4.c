/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_part4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disilva <disilva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 22:07:57 by disilva           #+#    #+#             */
/*   Updated: 2024/08/20 23:46:24 by disilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_2d_array(char **array)
{
	int	i;

	i = 0;
	if (array == NULL)
		return ;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
	array = NULL;
}

char	**combine_arrays(char **array_1,
char **array_2, int start, int *exp_flag)
{
	int		length_1;
	int		length_2;
	char	**new_array;
	int		i;
	int		j;

	length_1 = count_env_vars(array_1);
	length_2 = count_env_vars(array_2);
	new_array = ft_calloc((length_1 + length_2 + 1), sizeof(char *));
	if (!new_array)
		return (NULL);
	i = 0;
	while (array_1 && *(array_1 + i) && i < start)
	{
		*(new_array + i) = ft_strdup(*(array_1 + i));
		i++;
	}
	j = 0;
	while (array_2 && *(array_2 + j))
		*(new_array + i++) = ft_strdup(*(array_2 + j++));
	while (array_1 && *(array_1 + ++start))
		*(new_array + i++) = ft_strdup(*(array_1 + start));
	*(new_array + i) = NULL;
	return (free_2d_array(array_1), free_2d_array(array_2),
		*exp_flag = 0, new_array);
}

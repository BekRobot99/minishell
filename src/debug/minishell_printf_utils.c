/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_printf_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disilva <disilva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 19:50:07 by disilva           #+#    #+#             */
/*   Updated: 2024/08/20 23:19:37 by disilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_2d_array(char **arr, char *msg)
{
	int	i;

	i = 0;
	printf("\n%s\n", msg);
	while (arr[i])
	{
		printf("%p [%d] ----- %s\n", (arr + i), i, arr[i]);
		i++;
	}
}

void	print_tokens(const t_token_etw *cmds, char *msg)
{
	printf("\n%s\n", msg);
	if (cmds == NULL)
	{
		printf("Token is NULL\n");
		return ;
	}
	printf("Token:\n");
	printf("  Type: %d\n", cmds->kind);
	printf("  Value: %s\n", cmds->value);
	printf("  Next: %p\n", (void *)cmds->next);
	printf("  Prev: %p\n", (void *)cmds->previous);
}

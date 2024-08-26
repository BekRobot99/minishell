/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adjust_shell_lvl_part2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disilva <disilva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 21:59:18 by disilva           #+#    #+#             */
/*   Updated: 2024/08/20 22:13:06 by disilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_old_shell_level(char *env)
{
	char	*level;
	int		ind;

	ind = 0;
	if (!env)
		return (NULL);
	while (env[ind] != '=')
		ind++;
	level = ft_strdup(env + ind + 1);
	free_str(env);
	return (level);
}

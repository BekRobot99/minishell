/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_part2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disilva <disilva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 00:37:49 by disilva           #+#    #+#             */
/*   Updated: 2024/08/20 22:04:35 by disilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	print_newline(t_shell_config *info, int output)
{
	if (output != 0)
		ft_putstr_fd("\n", info->out_fd);
	info->exit_cd = 0;
}

char	*extract_home_path(char *home)
{
	int		start;
	int		index;
	char	*pose;

	start = ft_strlen(home);
	while (start > -1 && home[start] != '=')
		start--;
	pose = malloc(ft_strlen(home) - start);
	if (!pose)
		return (NULL);
	index = -1;
	while (home[++start] != '\0')
		pose[++index] = home[start];
	pose[++index] = '\0';
	return (pose);
}

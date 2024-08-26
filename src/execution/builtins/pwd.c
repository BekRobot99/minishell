/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disilva <disilva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 17:59:05 by disilva           #+#    #+#             */
/*   Updated: 2024/08/20 22:08:33 by disilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	ft_pwd(t_shell_config *info)
{
	char	*cwd;

	if (ft_strncmp(info->command_list->input_line[0], "pwd",
			ft_strlen(info->command_list->input_line[0])) == 0)
	{
		cwd = getcwd(NULL, 0);
		ft_putendl_fd(cwd, info->out_fd);
		free_str(cwd);
		info->exit_cd = 0;
	}
	else
		print_error_message_exit(info->command_list->input_line[0], 1, info);
}

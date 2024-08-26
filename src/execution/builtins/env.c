/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disilva <disilva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 17:59:25 by disilva           #+#    #+#             */
/*   Updated: 2024/08/20 23:37:30 by disilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	ft_env(t_shell_config *mini)
{
	int		i;

	i = -1;
	if (ft_strncmp(mini->command_list->input_line[0], "env", 4) == 0)
	{
		while (mini->envp[++i] != NULL)
			if (ft_strchr(mini->envp[i], '=') != NULL)
				ft_putendl_fd(mini->envp[i], mini->out_fd);
		mini->exit_cd = 0;
	}
	else
		print_error_message_exit(mini->command_list->input_line[0], 1, mini);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_part2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disilva <disilva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 21:51:48 by disilva           #+#    #+#             */
/*   Updated: 2024/08/20 23:10:15 by disilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	finalize(t_shell_config *config)
{
	if (config)
	{
		if (config->readline)
			free_str(config->readline);
		if (config->token_list && config->readline)
			free_token_list(config->token_list);
		if (config->envp)
			free_2d_array(config->envp);
		if (config->command_list && config->readline)
			free_commands(config->command_list);
		if (config->pwd)
			free_str(config->pwd);
		if (config->home)
			free_str(config->home);
	}
	config = NULL;
}

void	process_input(t_shell_config *config)
{
	if (config->readline[0] == '\0')
	{
		free_str(config->readline);
		return ;
	}
	add_history(config->readline);
	if (check_parsing(config) && config->command_list
		&& config->command_list->input_line
		&& config->command_list->input_line[0])
		execution_command(config);
	else
	{
		print_error(config->readline, config);
		free_str(config->readline);
		return ;
	}
	if (config->readline)
		free_str(config->readline);
}

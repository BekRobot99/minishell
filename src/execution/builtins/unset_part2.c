/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_part2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disilva <disilva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 00:38:35 by disilva           #+#    #+#             */
/*   Updated: 2024/08/20 22:08:45 by disilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	remove_elements(char **args_array, int *current_position,
int num_elements_to_remove)
{
	int	total_args;
	int	start_index;
	int	end_index;

	total_args = -1;
	start_index = *current_position - 1;
	end_index = *current_position;
	while (*(args_array + ++total_args))
		;
	while (end_index < *current_position + num_elements_to_remove)
		free_str(*(args_array + end_index++));
	while (++start_index < total_args - num_elements_to_remove)
		*(args_array + start_index) = *(args_array + start_index
				+ num_elements_to_remove);
	*(args_array + total_args - num_elements_to_remove) = NULL;
	(*current_position)--;
}

void	unset_variable(t_shell_config *info, int index)
{
	int	params;
	int	env_size;

	params = 0;
	if (find_env_var_index(info->envp, info->command_list->input_line[index],
			&params) != -1)
	{
		env_size = count_env_vars(info->envp);
		remove_element(info->envp, &params);
		info->envp[env_size] = NULL;
	}
}

void	ft_unset(t_shell_config *info)
{
	int	index;

	if (ft_strncmp(info->command_list->input_line[0], "unset", 6) != 0)
	{
		print_error_message_exit("Unset: ", 1, info);
		return ;
	}
	else if (info->command_list->input_line[1] == NULL)
		return ;
	handle_unset_errors(info);
	index = 0;
	while (info->command_list->input_line[++index] != NULL)
	{
		unset_variable(info, index);
	}
	info->exit_cd = ft_calculate_export_exit_status(info);
}

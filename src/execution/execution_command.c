/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_command.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disilva <disilva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 21:14:16 by disilva           #+#    #+#             */
/*   Updated: 2024/08/20 20:51:49 by disilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_commands(t_command_context *command_list)
{
	t_command_context	*current_list;

	current_list = NULL;
	while (command_list)
	{
		current_list = command_list;
		if (command_list->input_line)
			free_2d_array(command_list->input_line);
		command_list = command_list->next;
		free(current_list);
	}
}

void	free_token_list(t_token_etw *tokens_vals)
{
	t_token_etw	*current;
	t_token_etw	*next;

	if (!tokens_vals)
		return ;
	current = tokens_vals;
	while (current)
	{
		next = current->next;
		free(current->value);
		free(current);
		current = next;
	}
	tokens_vals = NULL;
}

int	ft_lstsize_commands(t_command_context *lst)
{
	int					index;
	t_command_context	*current;

	index = 0;
	current = lst;
	while (current)
	{
		current = current->next;
		index++;
	}
	return (index);
}

void	execution_command(t_shell_config *info)
{
	if (ft_strncmp(info->command_list->input_line[0], "&&", 3) == 0)
		print_error(info->command_list->input_line[0], info);
	else if (ft_strncmp(info->command_list->input_line[0], "exit", 5) == 0)
		ft_exit(info);
	else if (ft_lstsize_commands(info->command_list) == 1)
		exec_single_cmd(info);
	else if (ft_lstsize_commands(info->command_list) > 1)
		exec_multiple_cmd(info);
	else
		print_error_message_exit(info->command_list->input_line[0], 1, info);
	if (info->token_list)
		free_token_list(info->token_list);
	if (info->command_list)
		free_commands(info->command_list);
}

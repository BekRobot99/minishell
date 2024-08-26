/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_part3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disilva <disilva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 00:50:24 by disilva           #+#    #+#             */
/*   Updated: 2024/08/20 22:07:58 by disilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	ft_find_in_envp(char **envp, char *var)
{
	int	i;

	i = -1;
	while (envp[++i] != NULL)
	{
		if (ft_strncmp(envp[i], var, ft_strlen(var)) == 0
			&& (envp[i][ft_strlen(var)] == '='
			|| envp[i][ft_strlen(var)] == '\0'
			|| (envp[i][ft_strlen(var)] == '+' && envp[i][ft_strlen(var)
					+ 1] == '=')))
			return (i);
	}
	return (-1);
}

static int	handle_invalid_option_error(t_shell_config *input, int i)
{
	if (input->command_list->input_line[1][0] == '-')
	{
		if (i != 1)
			return (0);
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd("export: -", 2);
		ft_putchar_fd(input->command_list->input_line[i][1], 2);
		ft_putendl_fd(": invalid option", 2);
		ft_putendl_fd(ERROR_EXPORT_MSG, 2);
		return (0);
	}
	return (1);
}

static int	handle_invalid_export_string_error(t_shell_config *input, int i)
{
	if (ft_isdigit(input->command_list->input_line[i][0]) == 1)
	{
		print_error_message_extra("export: `",
			input->command_list->input_line[i], 4, input);
		return (0);
	}
	else if (!ft_check_export_string(input->command_list->input_line[i]))
	{
		print_error_message_extra("export: `",
			input->command_list->input_line[i], 4, input);
		return (0);
	}
	return (1);
}

int	handle_export_errors(t_shell_config *input, int i)
{
	if (!handle_invalid_option_error(input, i))
		return (0);
	if (!handle_invalid_export_string_error(input, i))
		return (0);
	return (1);
}

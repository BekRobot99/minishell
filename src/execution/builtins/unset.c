/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disilva <disilva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 17:58:56 by disilva           #+#    #+#             */
/*   Updated: 2024/08/20 22:08:53 by disilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	find_env_var_index(char **envp, char *var, int *params)
{
	*params = -1;
	while (envp[++(*params)] != NULL)
		if (ft_strncmp(var, envp[*params], ft_strlen(var)) == 0
			&& (envp[*params][ft_strlen(var)] == '='
			|| envp[*params][ft_strlen(var)] == '\0'))
			return (*params);
	return (-1);
}

int	is_valid_unset_identifier(char *str)
{
	int	idx;

	idx = -1;
	while (str[++idx] != '\0')
		if (ft_isalnum(str[idx]) != 1 && str[idx] != '_')
			return (0);
	return (1);
}

int	handle_unset_errors(t_shell_config *info)
{
	int	i;

	i = 0;
	while (info->command_list->input_line[++i] != NULL)
	{
		if (!is_valid_unset_identifier(info->command_list->input_line[i]))
		{
			print_error_message_extra("unset: `",
				info->command_list->input_line[i], 4, info);
		}
		else if (ft_isdigit(info->command_list->input_line[i][0]) == 1)
		{
			print_error_message_extra("unset: `",
				info->command_list->input_line[i], 4, info);
		}
	}
	return (1);
}

int	ft_check_export_string(char *s)
{
	int	idx;

	idx = -1;
	while (s[++idx] != '\0' && s[idx] != '=' && !(s[idx] == '+'
			&& s[idx + 1] == '='))
		if (ft_isalnum(s[idx]) != 1 && s[idx] != '_')
			return (0);
	return (1);
}

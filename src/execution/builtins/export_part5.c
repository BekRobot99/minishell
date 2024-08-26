/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_part5.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disilva <disilva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 23:28:07 by disilva           #+#    #+#             */
/*   Updated: 2024/08/20 23:42:49 by disilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	print_export_with_value(t_shell_config *out_fd, char **entry,
		int key)
{
	int	j;

	ft_putstr_fd("declare -x ", out_fd->out_fd);
	j = -1;
	while (entry[key][++j] != '\0' && entry[key][j] != '=')
		ft_putchar_fd(entry[key][j], out_fd->out_fd);
	ft_putstr_fd("=\"", out_fd->out_fd);
	while (entry[key][++j] != '\0')
		ft_putchar_fd(entry[key][j], out_fd->out_fd);
	ft_putstr_fd("\"\n", out_fd->out_fd);
}

void	print_export_without_value(t_shell_config *out_fd, char **entry,
		int key)
{
	if (ft_strncmp(entry[key], "OLDPWD", 7) != 0)
	{
		ft_putstr_fd("declare -x ", out_fd->out_fd);
		ft_putstr_fd(entry[key], out_fd->out_fd);
		ft_putstr_fd("\n", out_fd->out_fd);
	}
}

void	print_export_without_args(t_shell_config *out_fd, char **entry, int key,
int flag)
{
	if (flag == 1)
	{
		print_export_with_value(out_fd, entry, key);
	}
	else if (flag == 2)
	{
		print_export_without_value(out_fd, entry, key);
	}
}

void	update_existing_env_var(t_shell_config *input, char *envp, int j)
{
	int	var_index;

	var_index = find_var_index(input->envp, envp);
	if (!ft_strchr(input->envp[var_index], '=')
		&& (ft_strchr(input->command_list->input_line[j],
				'=') > ft_strchr(input->command_list->input_line[j], '+')))
	{
		ft_append_to_env_var_ex(input->envp, var_index,
			input->command_list->input_line[j], envp);
	}
	else if (ft_strchr(input->command_list->input_line[j], '=')
		&& ft_strchr(input->command_list->input_line[j], '+')
		&& (ft_strchr(input->command_list->input_line[j],
				'=') > ft_strchr(input->command_list->input_line[j], '+')))
	{
		ft_append_to_env_var(input->envp, var_index,
			input->command_list->input_line[j], envp);
	}
	else if (ft_has_value_after_equal(input->command_list->input_line[j]) != 0)
	{
		ft_replace_env_var(input->envp, input->command_list->input_line[j],
			envp);
	}
}

void	ft_export(t_shell_config *info)
{
	if (ft_strncmp(info->command_list->input_line[0], "export", 7) != 0)
		print_error_message_exit(info->command_list->input_line[0], 1, info);
	else if (info->command_list->input_line[1] == NULL
		&& ft_strlen(info->command_list->input_line[0]) == 6)
	{
		export_no_args(info);
		return ;
	}
	update_envp_size(info, -1, 0);
	info->exit_cd = ft_calculate_export_exit_status(info);
}

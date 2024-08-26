/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disilva <disilva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 17:59:30 by disilva           #+#    #+#             */
/*   Updated: 2024/08/20 23:20:37 by disilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	is_echo_n_option(char *str)
{
	int	index;

	if (ft_strncmp(str, "-n", 2) == 0)
	{
		index = 1;
		while (str[++index] != '\0' && str[0] == '-' && str[index] == 'n')
			if (str[index] != 'n' && index > 1)
				return (0);
		if (index == (int)ft_strlen(str))
			return (1);
	}
	return (0);
}

void	print_home_directory(t_shell_config *info)
{
	char	*home;
	char	*pose;

	home = get_env_var(info, "HOME");
	if (!home)
		home = info->home;
	else
		home = strip_path(home);
	pose = extract_home_path(home);
	if (!pose)
	{
		free(home);
		return ;
	}
	ft_putstr_fd(pose, info->out_fd);
	free(home);
	free(pose);
}

void	print_echo_argument(t_shell_config *info, int increment)
{
	if (is_echo_n_option(info->command_list->input_line[increment]))
		return ;
	if (increment != 0)
		ft_putstr_fd(" ", info->out_fd);
	if (info->command_list->input_line[increment] == NULL)
		return ;
	if (ft_strncmp(info->command_list->input_line[increment], "~", 2) == 0)
		print_home_directory(info);
	else
		ft_putstr_fd(info->command_list->input_line[increment], info->out_fd);
}

void	process_echo_argument(t_shell_config *info,
int *input, int *output, int i)
{
	if (is_echo_n_option(info->command_list->input_line[i]) && *input != 0)
	{
		*output = 0;
	}
	else
	{
		*input = 0;
		print_echo_argument(info, i);
		if (info->command_list->input_line[i + 1] != NULL)
		{
			ft_putstr_fd(" ", info->out_fd);
		}
	}
}

void	ft_echo(t_shell_config *info, int input)
{
	int	output;
	int	i;

	i = 0;
	output = 1;
	if (ft_strncmp(info->command_list->input_line[0], "echo", 5) == 0)
	{
		while (info->command_list->input_line[++i] != NULL)
		{
			process_echo_argument(info, &input, &output, i);
		}
		print_newline(info, output);
	}
	else
	{
		print_error_message_exit(info->command_list->input_line[0], 1, info);
	}
}

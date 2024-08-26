/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disilva <disilva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 17:59:16 by disilva           #+#    #+#             */
/*   Updated: 2024/08/20 23:44:12 by disilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

long long	ft_atoll(const char *str)
{
	long long	i;
	long long	sign;
	long long	result;

	i = 0;
	sign = 1;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	result = 0;
	while (str[i] != '\0' && str[i] >= 48 && str[i] <= 57)
	{
		result = (result * 10) + (str[i] - 48);
		i++;
	}
	return (result * sign);
}

int	is_numeric_string(char *str)
{
	int	i;
	int	flag;

	i = -1;
	flag = 0;
	while (str[++i] != '\0')
	{
		if ((!ft_isdigit(str[i]) && str[i] != '+' && str[i] != '-') || flag > 1)
			return (0);
		if (str[i] == '+' || str[i] == '-')
			flag++;
	}
	return (1);
}

void	terminate_shell(t_shell_config *env, int c)
{
	ft_putendl_fd("exit", 1);
	finalize(env);
	free(env->terminal_name);
	exit(c);
}

int	determine_exit_action(t_shell_config *info)
{
	if (ft_strncmp(info->command_list->input_line[0], "exit", 5) != 0)
		return (1);
	else if (count_env_vars(info->command_list->input_line) > 1
		&& !is_numeric_string(info->command_list->input_line[1]))
		return (2);
	else if (count_env_vars(info->command_list->input_line) == 1)
		return (3);
	else if (count_env_vars(info->command_list->input_line) == 2)
		return (4);
	else if (count_env_vars(info->command_list->input_line) > 2
		&& is_numeric_string(info->command_list->input_line[1]))
		return (5);
	return (1);
}

void	ft_exit(t_shell_config *mini)
{
	int	action;

	adjust_shell_lvl(mini, 0);
	action = determine_exit_action(mini);
	if (action == 1)
		print_error_message_exit(mini->command_list->input_line[0], 1, mini);
	else if (action == 2)
		print_error_message("exit: ",
			mini->command_list->input_line[1], 1, mini);
	else if (action == 3)
		terminate_shell(mini, mini->exit_cd);
	else if (action == 4)
		terminate_shell(mini, ft_atoll(mini->command_list->input_line[1]));
	else if (action == 5)
		print_error_message("exit", NULL, 2, mini);
	else
		print_error_message_exit(mini->command_list->input_line[0], 1, mini);
}

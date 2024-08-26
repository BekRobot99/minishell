/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_commands_part2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disilva <disilva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 21:42:50 by disilva           #+#    #+#             */
/*   Updated: 2024/08/20 22:10:15 by disilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exec_command(char *exec_path, t_shell_config *env_vars, int *exit_code)
{
	if (execve(exec_path, env_vars->command_list->input_line, env_vars->envp)
		== -1)
	{
		print_error_message_exit(env_vars->command_list->input_line[0],
			1, env_vars);
		free_str(exec_path);
		env_vars->exit_cd = 127;
		exit(env_vars->exit_cd);
	}
	(void)exit_code;
	finalize(env_vars);
	exit(EXIT_SUCCESS);
}

void	setup_fds(t_shell_config *info, int index)
{
	if (info->command_list->input_fd != STDIN_FILENO)
	{
		if (dup2(info->fds[index][0], STDIN_FILENO) == -1)
			fatal_error("Dup 7");
		close(info->command_list->input_fd);
	}
	if (info->command_list->output_fd != STDOUT_FILENO)
	{
		if (dup2(info->fds[index][1], STDOUT_FILENO) == -1)
			fatal_error("Dup 8");
		close(info->command_list->output_fd);
	}
}

int	is_builtin(t_shell_config *info)

{
	if (ft_strncmp(info->command_list->input_line[0], "pwd", 4) == 0)
		return (1);
	else if (ft_strncmp(info->command_list->input_line[0], "cd", 3) == 0)
		return (1);
	else if (ft_strncmp(info->command_list->input_line[0], "echo", 5) == 0)
		return (1);
	else if (ft_strncmp(info->command_list->input_line[0], "export", 7) == 0)
		return (1);
	else if (ft_strncmp(info->command_list->input_line[0], "env", 4) == 0)
		return (1);
	else if (ft_strncmp(info->command_list->input_line[0], "unset", 6) == 0)
		return (1);
	return (0);
}

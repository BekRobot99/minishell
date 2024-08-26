/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disilva <disilva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 06:17:42 by abekri            #+#    #+#             */
/*   Updated: 2024/08/20 22:09:47 by disilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	configure_io_redirection(t_shell_config *fd_info, int size)
{
	close_file_descriptors(fd_info->fds, size);
	if (fd_info->command_list->input_fd != STDIN_FILENO)
	{
		if (dup2(fd_info->command_list->input_fd, STDIN_FILENO) == -1)
			fatal_error("Dup 5");
		close(fd_info->command_list->input_fd);
	}
	if (fd_info->command_list->output_fd != STDOUT_FILENO)
	{
		if (dup2(fd_info->command_list->output_fd, STDOUT_FILENO) == -1)
			fatal_error("Dup 6");
		close(fd_info->command_list->output_fd);
	}
}

void	setup_file_descriptors(t_shell_config *fd_info, int i, int size)
{
	if (i == 0)
	{
		if (dup2(fd_info->fds[i][1], STDOUT_FILENO) == -1)
			fatal_error("Dup 1");
	}
	else if (fd_info->command_list->next == NULL)
	{
		if (dup2(fd_info->fds[i - 1][0], STDIN_FILENO) == -1)
			fatal_error("Dup 2");
	}
	else
	{
		if (dup2(fd_info->fds[i - 1][0], STDIN_FILENO) == -1)
			fatal_error("Dup 3");
		if (dup2(fd_info->fds[i][1], STDOUT_FILENO) == -1)
			fatal_error("Dup 4");
	}
	configure_io_redirection(fd_info, size);
}

void	execute_child_process(t_shell_config *info, char
*path, int fd_info, int exit_cd)
{
	setup_file_descriptors(info, fd_info, exit_cd);
	if (is_builtin(info))
	{
		run_builtin(info);
		free_str(path);
		exit(EXIT_SUCCESS);
	}
	if (execve(path, info->command_list->input_line, info->envp) == -1)
	{
		free_str(path);
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(info->command_list->input_line[0], 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd("command not found", 2);
		exit(127);
	}
	finalize(info);
	exit(EXIT_SUCCESS);
}

void	handle_child_process(t_shell_config *exec_params, int i, int size)
{
	char	*path;

	path = NULL;
	if (!is_builtin(exec_params))
	{
		path = find_exec_path(exec_params,
				exec_params->command_list->input_line[0], 0);
		if (!path)
			return ;
	}
	execute_child_process(exec_params, path, i, size);
}

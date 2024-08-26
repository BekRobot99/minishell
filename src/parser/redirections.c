/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disilva <disilva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 05:37:35 by abekri            #+#    #+#             */
/*   Updated: 2024/08/20 23:22:01 by disilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	verify_fd_perm(char *file_path)
{
	struct stat	file_stat;

	if (stat(file_path, &file_stat) == 0)
	{
		if (access(file_path, R_OK) == -1)
		{
			ft_putstr_fd("minishell", STDERR_FILENO);
			ft_putstr_fd(": ", STDERR_FILENO);
			ft_putstr_fd(file_path, STDERR_FILENO);
			ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
			return (0);
		}
	}
	return (1);
}

int	verify_fd_type(char *file_path)
{
	struct stat	file_info;

	if (stat(file_path, &file_info) == 0)
	{
		if (S_ISDIR(file_info.st_mode))
		{
			ft_putstr_fd("minishell ", STDERR_FILENO);
			ft_putstr_fd(file_path, STDERR_FILENO);
			ft_putstr_fd(": is a directory\n", STDERR_FILENO);
			return (0);
		}
	}
	return (1);
}

int	handle_output_append(t_command_context *head_cmds, int *arg_index)
{
	if (head_cmds->output_fd != STDOUT_FILENO)
		close(head_cmds->output_fd);
	if (ft_strncmp(*(head_cmds->input_line + *arg_index), ">", 2) == 0)
		head_cmds->output_fd = open(*(head_cmds->input_line + *arg_index + 1),
				O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (ft_strncmp(*(head_cmds->input_line + *arg_index), ">>", 2) == 0)
		head_cmds->output_fd = open(*(head_cmds->input_line + *arg_index + 1),
				O_CREAT | O_RDWR | O_APPEND, 0644);
	if (head_cmds->output_fd == -1)
		return (ft_putstr_fd(TERMINAL_NAME, STDERR_FILENO), 0);
	return (remove_elements(head_cmds->input_line, arg_index, 2), 1);
}

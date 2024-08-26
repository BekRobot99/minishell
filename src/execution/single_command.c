/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disilva <disilva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 02:26:34 by disilva           #+#    #+#             */
/*   Updated: 2024/08/20 22:09:54 by disilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_error_message(char *message1, char *message2, int c,
		t_shell_config *info)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(message1, 2);
	if (message2 != NULL)
		ft_putstr_fd(message2, 2);
	if (c == 1)
	{
		ft_putendl_fd(": numeric argument required", 2);
		finalize(info);
		exit(255);
	}
	else if (c == 2)
	{
		ft_putendl_fd(": too many arguments", 2);
		info->exit_cd = 1;
	}
	else if (c == 3)
	{
		ft_putendl_fd(": OLDPWD not set", 2);
		info->exit_cd = 1;
	}
	else if (c == 4)
	{
		ft_putendl_fd(": HOME not set", 2);
		info->exit_cd = 1;
	}
}

void	print_error_message_exit(char *message, int c, t_shell_config *info)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(message, 2);
	if (c == 1)
	{
		ft_putendl_fd(": command not found", 2);
		info->exit_cd = 127;
	}
	else if (c == 2)
	{
		ft_putendl_fd(": No such file or directory", 2);
		info->exit_cd = 1;
	}
	else if (c == 3)
	{
		ft_putendl_fd(": not enough arguments", 2);
		info->exit_cd = 1;
	}
	else if (c == 4)
	{
		ft_putendl_fd(": HOME not set", 2);
		info->exit_cd = 1;
	}
}

void	fatal_error(char *message)
{
	perror(message);
	exit(1);
}

int	**create_fds(t_shell_config *info, int num_pairs, int use_pipes)
{
	int	i;

	info->fds = malloc(num_pairs * sizeof(int *));
	if (!info->fds)
		fatal_error("Malloc fd");
	i = -1;
	while (++i < num_pairs)
	{
		info->fds[i] = malloc(2 * sizeof(int));
		if (!info->fds[i])
			fatal_error("Malloc fd[i]");
		if (use_pipes)
			if (pipe(info->fds[i]) < 0)
				fatal_error("Pipe");
	}
	if (!use_pipes)
	{
		info->fds[0][0] = dup(STDIN_FILENO);
		info->fds[0][1] = dup(STDOUT_FILENO);
		info->fds[1][0] = info->command_list->input_fd;
		info->fds[1][1] = info->command_list->output_fd;
	}
	return (info->fds);
}

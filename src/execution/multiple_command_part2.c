/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_command_part2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disilva <disilva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 21:47:42 by disilva           #+#    #+#             */
/*   Updated: 2024/08/20 22:09:23 by disilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_file_discriptor(int **fd, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (fd[i])
			free(fd[i]);
		i++;
	}
	free(fd);
}

void	close_file_descriptors(int **fd, int size)
{
	int	i;

	i = -1;
	while (++i < size)
	{
		close(fd[i][0]);
		close(fd[i][1]);
	}
}

void	wait_for_child_processes(t_shell_config *info, int lst_size)
{
	int	i;
	int	status;

	i = -1;
	close_file_descriptors(info->fds, lst_size);
	while (++i < lst_size)
	{
		waitpid(info->var_pids[i], &status, 0);
		if WIFEXITED (status)
			info->exit_cd = WEXITSTATUS(status);
		if WIFSIGNALED (status)
			info->exit_cd = WTERMSIG(status) + 128;
	}
	free(info->var_pids);
	free_file_discriptor(info->fds, lst_size);
	g_signal = 0;
	setup_signal_handlers(info);
}

void	exec_multiple_cmd(t_shell_config *info)
{
	t_command_context	*vars;
	int					i;
	int					list_len;

	start_signal_handlers(info);
	list_len = ft_lstsize_commands(info->command_list);
	info->fds = create_fds(info, list_len, 1);
	info->var_pids = malloc(ft_lstsize_commands(info->command_list)
			* sizeof(int));
	if (!info->var_pids)
		fatal_error("Malloc var_pids");
	i = -1;
	vars = info->command_list;
	while (info->command_list != NULL && ++i < list_len)
	{
		info->var_pids[i] = fork();
		if (info->var_pids[i] == -1)
			fatal_error("single exec fork() fail");
		if (info->var_pids[i] == 0)
			handle_child_process(info, i, list_len);
		info->command_list = info->command_list->next;
	}
	info->command_list = vars;
	wait_for_child_processes(info, list_len);
}

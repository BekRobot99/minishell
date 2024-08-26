/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_commands_part5.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disilva <disilva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 21:46:02 by disilva           #+#    #+#             */
/*   Updated: 2024/08/20 23:19:58 by disilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/signals.h"

void	exec_single_cmd_execution(t_shell_config *vars, int pid, char *envp,
		int *exit_cd)
{
	int	status;

	(void)exit_cd;
	ft_reset_io(vars, 0);
	waitpid(pid, &status, 0);
	if WIFEXITED (status)
		vars->exit_cd = WEXITSTATUS(status);
	if WIFSIGNALED (status)
		vars->exit_cd = WTERMSIG(status) + 128;
	free_str(envp);
	g_signal = 0;
}

static void	handle_command_execution(t_shell_config *info, char *vars_path)
{
	int	vars_pid;

	vars_pid = fork();
	if (vars_pid == -1)
	{
		fatal_error("single exec fork() fail");
		return ;
	}
	else if (vars_pid == 0)
	{
		exec_command(vars_path, info, NULL);
		exit(EXIT_FAILURE);
	}
	exec_single_cmd_execution(info, vars_pid, vars_path, NULL);
}

void	exec_single_cmd(t_shell_config *info)
{
	char	*vars_path;

	g_signal = 1;
	start_signal_handlers(info);
	info->fds = create_fds(info, 2, 0);
	setup_fds(info, 1);
	if (is_builtin(info))
	{
		run_builtin(info);
		ft_reset_io(info, 0);
		return ;
	}
	vars_path = ft_strdup(info->command_list->input_line[0]);
	vars_path = find_exec_path(info, vars_path, 0);
	if (!vars_path)
		return ;
	handle_command_execution(info, vars_path);
	setup_signal_handlers(info);
}

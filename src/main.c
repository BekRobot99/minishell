/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disilva <disilva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 22:46:27 by abekri            #+#    #+#             */
/*   Updated: 2024/08/20 23:09:53 by disilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/signals.h"

int	g_signal = 0;

int	main(int argc, char *argv[], char *envp[])
{
	t_shell_config	minishell_data;
	int				exit_msg;

	(void)argv;
	exit_msg = 1;
	if (argc != 1 || !*envp)
		return (exit_msg);
	setup_signal_handlers(&minishell_data);
	start_info_ms(&minishell_data, envp);
	rl_bind_key('\t', rl_complete);
	using_history();
	start_iterm(&minishell_data);
	rl_clear_history();
	return (exit_msg = minishell_data.exit_cd, printf("exit\n"), exit_msg);
}

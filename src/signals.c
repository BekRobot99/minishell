/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disilva <disilva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 22:45:15 by abekri            #+#    #+#             */
/*   Updated: 2024/08/20 20:53:18 by disilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	signal_handler(int sig)
{
	char	*temp;

	(void)sig;
	temp = ft_strjoin(rl_line_buffer, "  ");
	rl_replace_line(temp, 0);
	free(temp);
	rl_redisplay();
	ft_putchar_fd('\n', STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sigquit_handler(int signo)
{
	if (signo == SIGQUIT)
	{
		ft_putstr_fd("Quit: 3", 1);
	}
	ft_putchar_fd('\n', 1);
}

void	start_signal_handlers(t_shell_config *config)
{
	(void)config;
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, sigquit_handler);
}

void	setup_signal_handlers(t_shell_config *config)
{
	(void)config;
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}

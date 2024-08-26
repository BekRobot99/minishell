/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disilva <disilva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 22:46:20 by abekri            #+#    #+#             */
/*   Updated: 2024/08/20 23:19:22 by disilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

void	signal_handler(int sig);
void	sigquit_handler(int signo);
void	start_signal_handlers(t_shell_config *config);

#endif

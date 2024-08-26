/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disilva <disilva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 22:46:27 by abekri            #+#    #+#             */
/*   Updated: 2024/08/20 23:10:22 by disilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_error(char *s, t_shell_config *config)
{
	if (s[0] == '\"' && s[1] == '\"')
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd("", 2);
		ft_putendl_fd(": command not found", 2);
		config->exit_cd = 127;
	}
	if (ft_strncmp(s, "&&", 3) == 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd("syntax error near unexpected token `", 2);
		ft_putstr_fd(s, 2);
		ft_putendl_fd("\'", 2);
		config->exit_cd = 258;
	}
}

void	display_tokenz(t_token_etw *info, char *msg)
{
	t_token_etw	*current;

	printf("\n%s\n", msg);
	current = info;
	while (current != NULL)
	{
		print_tokens(current, msg);
		current = current->next;
	}
}

int	check_parsing(t_shell_config *config)
{
	if (!perform_lexical_analysis(config))
		return (0);
	if (!check_syntax(config))
		return (0);
	if (!generate_abstract_cmds(config))
		return (0);
	if (!expansion_success(config))
		return (0);
	if (!handle_redirections(config))
		return (0);
	return (1);
}

void	start_iterm(t_shell_config *config)
{
	while (1)
	{
		g_signal = 0;
		config->readline = readline(config->terminal_name);
		if (!config->readline)
			break ;
		process_input(config);
	}
	return (finalize(config), free(config->terminal_name));
}

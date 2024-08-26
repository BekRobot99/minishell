/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disilva <disilva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 02:32:54 by abekri            #+#    #+#             */
/*   Updated: 2024/08/20 20:52:27 by disilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_pipe_err(t_token_etw *tokens)
{
	if (tokens->kind == '|')
	{
		if (tokens->next->kind == '|')
			return (0);
		if (!tokens->previous)
			return (0);
		if (tokens->previous->kind == '|')
			return (0);
		if (!tokens->next)
			return (0);
		if (tokens->next->kind == EOL)
			return (0);
	}
	return (1);
}

int	check_redir_err(t_token_etw *token)
{
	if (token->kind == '<' || token->kind == '>'
		|| token->kind == R_DIR_APPEND || token->kind == H_DOC)
	{
		if (token->next->kind != WORD && token->next->kind == EOL)
			return (0);
		else if (!token->previous && token->next->kind != WORD)
			return (0);
	}
	return (1);
}

int	check_syntax(t_shell_config *info)
{
	t_token_etw	*i;

	i = info->token_list;
	while (i)
	{
		if (!check_pipe_err(i) || !check_redir_err(i))
			return (info->exit_cd = 2,
				free_token_list(info->token_list), 0);
		i = i->next;
	}
	return (1);
}

void	print_error_message_extra(char *message1, char *message2, int c,
		t_shell_config *exit_code_array)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(message1, 2);
	ft_putstr_fd(message2, 2);
	if (c == 1)
	{
		ft_putendl_fd(": command not found", 2);
		exit_code_array->exit_cd = 127;
	}
	else if (c == 2)
	{
		ft_putendl_fd(": No such file or directory", 2);
		exit_code_array->exit_cd = 1;
	}
	else if (c == 3)
	{
		ft_putendl_fd(": not enough arguments", 2);
		exit_code_array->exit_cd = 1;
	}
	else if (c == 4)
	{
		ft_putendl_fd("': not a valid identifier", 2);
		exit_code_array->exit_cd = 1;
	}
}

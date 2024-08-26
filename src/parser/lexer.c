/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disilva <disilva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 21:47:56 by abekri            #+#    #+#             */
/*   Updated: 2024/08/20 23:21:53 by disilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	init_lexer_dto(t_analyse *envp, char *s)
{
	envp->read_line = ft_strdup(s);
	envp->position = 0;
	envp->isdouble_quote = 0;
	envp->is_single_quote = 0;
}

int	start_tokens(t_analyse *info, t_shell_config *str)
{
	init_lexer_dto(info, str->readline);
	str->token_list = get_next_token(info);
	str->token_list->previous = NULL;
	if (!info->read_line || !str->token_list)
		return (0);
	return (1);
}

int	process_tokens(t_token_etw *ptr, t_analyse *info, t_shell_config *config)
{
	t_token_etw	*next;

	ptr->next = get_next_token(info);
	if (!ptr->next || ptr->kind == ERR)
	{
		ft_putendl_fd("minishell: syntax error unclosed quotes\n", 2);
		config->exit_cd = 258;
		free_str(info->read_line);
		return (0);
	}
	next = ptr;
	ptr->next->previous = next;
	return (1);
}

int	perform_lexical_analysis(t_shell_config *config)
{
	t_token_etw	*ptr;
	t_analyse	info;

	if (!start_tokens(&info, config))
		return (0);
	ptr = config->token_list;
	while (ptr->kind != EOL)
	{
		if (!process_tokens(ptr, &info, config))
			return (0);
		ptr = ptr->next;
	}
	if (DEBUG)
		display_tokenz(config->token_list, "TOKENS");
	return (free_str(info.read_line), 1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_part2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disilva <disilva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 22:03:14 by disilva           #+#    #+#             */
/*   Updated: 2024/08/21 00:29:50 by disilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	manage_quotes(t_analyse *pos_info)
{
	if (*(pos_info->read_line + pos_info->position) == (char) '\''
		&& *(pos_info->read_line + (pos_info->position - 1)) != (char) '\\'
		&& !pos_info->isdouble_quote && !pos_info->is_single_quote)
		pos_info->is_single_quote = 1;
	else if (*(pos_info->read_line + pos_info->position) == (char) '\''
		&& *(pos_info->read_line + (pos_info->position - 1)) != (char) '\\'
		&& !pos_info->isdouble_quote && pos_info->is_single_quote)
		pos_info->is_single_quote = 0;
	else if (*(pos_info->read_line + pos_info->position) == (char) '\"'
		&& *(pos_info->read_line + (pos_info->position - 1)) != (char) '\\'
		&& !pos_info->isdouble_quote && !pos_info->is_single_quote)
		pos_info->isdouble_quote = 1;
	else if (*(pos_info->read_line + pos_info->position) == (char) '\"'
		&& *(pos_info->read_line + (pos_info->position - 1)) != (char) '\\'
		&& pos_info->isdouble_quote && !pos_info->is_single_quote)
		pos_info->isdouble_quote = 0;
}

char	*extract_token_word_new_word(t_analyse *token_info, int start)
{
	char	*word;

	word = ft_calloc(sizeof(char), (size_t)(token_info->position - start + 1));
	ft_strlcpy(word, (token_info->read_line + start), (token_info->position
			- start + 1));
	return (word);
}

t_token_etw	*extract_token_word(t_analyse *token_info)
{
	int		start;
	char	*word;

	start = token_info->position;
	while (*(token_info->read_line + token_info->position))
	{
		if (*(token_info->read_line + token_info->position) == (char) '\''
			|| *(token_info->read_line + token_info->position) == (char) '\"')
			manage_quotes(token_info);
		if (!token_info->isdouble_quote && ft_is_space(*(token_info->read_line
					+ token_info->position)) && !token_info->is_single_quote)
			break ;
		if (!token_info->is_single_quote && (*(token_info->read_line
					+ token_info->position) == (char)PIPE
				|| *(token_info->read_line + token_info->position) == (char) '<'
				|| *(token_info->read_line
					+ token_info->position) == (char) '>')
			&& !token_info->isdouble_quote)
			break ;
		token_info->position++;
	}
	if (token_info->isdouble_quote || token_info->is_single_quote)
		return (build_token(ERR, NULL, NULL, NULL));
	word = extract_token_word_new_word(token_info, start);
	return (build_token(WORD, word, NULL, NULL));
}

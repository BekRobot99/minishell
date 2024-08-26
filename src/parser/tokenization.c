/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disilva <disilva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 00:45:05 by abekri            #+#    #+#             */
/*   Updated: 2024/08/20 22:12:51 by disilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_is_space(int c)
{
	if ((c && c == ' ') || ((c >= 9 && c <= 13)))
		return (1);
	return (0);
}

t_token_etw	*get_next_token(t_analyse *info)
{
	while (info->position < (int)ft_strlen(info->read_line))
	{
		if (ft_is_space(*(info->read_line + info->position)))
			info->position++;
		else if (*(info->read_line + info->position) == (char)PIPE)
			return (info->position++, build_token(PIPE, NULL, NULL, NULL));
		else if (*(info->read_line + info->position) == (char) '<'
			&& *(info->read_line + info->position + 1) != '<')
			return (info->position++, build_token('<', NULL, NULL, NULL));
		else if (*(info->read_line + info->position) == (char) '<'
			&& *(info->read_line + info->position + 1) == (char) '<')
			return (info->position += 2, build_token(H_DOC, NULL, NULL, NULL));
		else if (*(info->read_line + info->position) == (char) '>'
			&& *(info->read_line + info->position + 1) != (char) '>')
			return (info->position++, build_token('>', NULL, NULL, NULL));
		else if (*(info->read_line + info->position) == (char) '>'
			&& *(info->read_line + info->position + 1) == (char) '>')
			return (info->position += 2, build_token(R_DIR_APPEND, NULL, NULL,
					NULL));
		else if (!ft_is_space(*(info->read_line + info->position)))
			return (extract_token_word(info));
	}
	return (build_token(EOL, NULL, NULL, NULL));
}

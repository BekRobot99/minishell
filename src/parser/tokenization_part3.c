/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_part3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disilva <disilva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 22:05:54 by disilva           #+#    #+#             */
/*   Updated: 2024/08/20 22:12:29 by disilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token_etw	*build_token(t_tokenize_type type, char *val,
		t_token_etw *token_next, t_token_etw *token_prev)
{
	t_token_etw	*out;

	out = (t_token_etw *)malloc(sizeof(t_token_etw));
	if (!out)
		return (NULL);
	out->kind = type;
	if (type == PIPE)
		out->value = ft_strdup("|");
	else if (type == R_DIR_APPEND)
		out->value = ft_strdup(">>");
	else if (type == H_DOC)
		out->value = ft_strdup("<<");
	else if (type == EOL)
		out->value = ft_strdup("EOL");
	else
		out->value = val;
	out->next = token_next;
	out->previous = token_prev;
	return (out);
}

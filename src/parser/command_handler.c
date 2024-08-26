/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disilva <disilva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 03:34:28 by abekri            #+#    #+#             */
/*   Updated: 2024/08/20 22:11:09 by disilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	start_abstract(t_command_context **input)
{
	(*input) = (t_command_context *)malloc(sizeof(t_command_context));
	if (!(*input))
		return ;
	(*input)->input_line = NULL;
	(*input)->next = NULL;
	(*input)->input_fd = STDIN_FILENO;
	(*input)->output_fd = STDOUT_FILENO;
	(*input)->previous = NULL;
}

int	add_cmd_node(t_token_etw **cmds, t_command_context **cmds_head)
{
	t_token_etw			*previous_cmds_head;
	t_command_context	*new_cmds;
	t_command_context	*previous_cmds;

	new_cmds = NULL;
	start_abstract(&new_cmds);
	if (!new_cmds)
		return (0);
	if (*cmds_head)
	{
		previous_cmds = *cmds_head;
		while (previous_cmds && previous_cmds->next)
			previous_cmds = previous_cmds->next;
		previous_cmds->next = new_cmds;
		new_cmds->previous = previous_cmds;
	}
	else
		*cmds_head = new_cmds;
	previous_cmds_head = (*cmds)->previous;
	if (previous_cmds_head && previous_cmds_head->kind != PIPE)
		(*cmds) = (*cmds)->next;
	return (1);
}

int	create_args_array(t_token_etw **tokens, t_command_context **cmds_head,
		int arg_count)
{
	int	i;

	i = -1;
	while (++i < arg_count)
	{
		if ((*tokens)->kind == WORD)
			*((*cmds_head)->input_line + i) = ft_strdup((*tokens)->value);
		else
		{
			if ((*tokens)->kind == '<')
				*((*cmds_head)->input_line + i) = ft_strdup("<");
			else if ((*tokens)->kind == '>')
				*((*cmds_head)->input_line + i) = ft_strdup(">");
			else if ((*tokens)->kind == R_DIR_APPEND)
				*((*cmds_head)->input_line + i) = ft_strdup(">>");
			else if ((*tokens)->kind == H_DOC)
				*((*cmds_head)->input_line + i) = ft_strdup("<<");
		}
		if (!*((*cmds_head)->input_line + i))
			return (0);
		(*tokens) = (*tokens)->next;
	}
	return (1);
}

int	initialize_args(t_token_etw **tokens, t_command_context **cmds)
{
	t_token_etw			*arg_count;
	int					i;
	t_command_context	*args;

	i = 0;
	arg_count = *tokens;
	args = *cmds;
	while (arg_count && arg_count->kind != PIPE && arg_count->kind != EOL
		&& ++i)
		arg_count = arg_count->next;
	if (!i)
		return (1);
	while (args && (args)->next)
		args = (args)->next;
	(args)->input_line = (char **)malloc(sizeof(char *) * (i + 1));
	if (!(args)->input_line)
		return (0);
	if (!create_args_array(tokens, &args, i))
		return (0);
	*((args)->input_line + i) = NULL;
	if (DEBUG)
		print_2d_array((args)->input_line, "ARGS After init");
	return (1);
}

int	generate_abstract_cmds(t_shell_config *info)
{
	t_token_etw			*cmds;
	t_command_context	*cmd_count;

	cmds = info->token_list;
	cmd_count = NULL;
	while (cmds && cmds->kind != EOL)
	{
		if (!cmds->previous || cmds->previous->kind == PIPE)
		{
			if (!add_cmd_node(&cmds, &cmd_count))
				return (0);
		}
		if (cmds->kind != PIPE)
		{
			if (!initialize_args(&cmds, &cmd_count))
				return (0);
		}
		else if (cmds->kind == PIPE)
			cmds = cmds->next;
	}
	info->command_list = cmd_count;
	if (DEBUG)
		print_commands_part2(info->command_list, "---AFTER---");
	return (1);
}

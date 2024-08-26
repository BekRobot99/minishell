/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_part5.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disilva <disilva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 22:08:12 by disilva           #+#    #+#             */
/*   Updated: 2024/08/20 22:11:40 by disilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	remove_element(char **cmds, int *j)
{
	int	tmp;
	int	i;

	tmp = -1;
	i = *j - 1;
	while (*(cmds + ++tmp))
		;
	if (*(cmds + *j))
		free_str(*(cmds + *j));
	while (++i < tmp - 1)
		*(cmds + i) = *(cmds + i + 1);
	*(cmds + tmp - 1) = NULL;
	(*j)--;
}

int	expansion_success(t_shell_config *info)
{
	t_command_context	*cmds;
	int					exp_flag;
	int					index;

	exp_flag = 0;
	cmds = info->command_list;
	while (cmds)
	{
		if (DEBUG)
			print_2d_array(cmds->input_line, "before expansion");
		index = -1;
		while (cmds->input_line && *(cmds->input_line + ++index))
		{
			if (!needs_expansion(info, (cmds->input_line + index), &exp_flag))
				remove_element(cmds->input_line, &index);
			if (exp_flag)
				cmds->input_line = combine_arrays(cmds->input_line,
						ft_split(*(cmds->input_line + index), ' '), index,
						&exp_flag);
		}
		if (DEBUG)
			print_2d_array(cmds->input_line, "after expansion");
		cmds = cmds->next;
	}
	return (1);
}

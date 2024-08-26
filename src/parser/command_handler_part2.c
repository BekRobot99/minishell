/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_handler_part2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disilva <disilva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 21:49:09 by disilva           #+#    #+#             */
/*   Updated: 2024/08/20 22:10:45 by disilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_commands_part2(t_command_context *command, char *cmds)
{
	if (!command)
		printf("The command is NULL\n");
	while (command)
	{
		printf("Arguments:\n");
		if (command->input_line)
			print_2d_array(command->input_line, cmds);
		else
			printf("  args: NULL\n");
		printf("fd_infile: %d\n", command->input_fd);
		printf("fd_outfile: %d\n", command->output_fd);
		printf("Next command: %p\n", (void *)command->next);
		printf("Previous command: %p\n", (void *)command->previous);
		command = command->next;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_term.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disilva <disilva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 20:09:28 by abekri            #+#    #+#             */
/*   Updated: 2024/08/20 23:22:23 by disilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	params_start(t_token_etw *args, char *s)
{
	args->cmd_args = malloc(sizeof(char *) * 2);
	args->cmd_args[0] = ft_strdup(s);
	args->cmd_args[1] = NULL;
	args->output = malloc(sizeof(char) * BUFFER_SIZE);
}

void	get_args_empty(t_token_etw *args)
{
	int	i;

	if (args->cmd_args)
	{
		i = 0;
		while (args->cmd_args[i])
		{
			free_str(args->cmd_args[i]);
			i++;
		}
		free_str(args->cmd_args[1]);
		free_2d_array(args->cmd_args);
	}
}

void	perform_child_process_and_store_output(t_token_etw *args)
{
	pid_t	pid;
	int		pipefd[2];

	if (pipe(pipefd) == -1)
		return (perror("Pipe error"));
	pid = fork();
	if (pid == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		if (execve(args->cmd_args[0], args->cmd_args, NULL) == -1)
			return (perror("exceve error"));
	}
	else
	{
		wait(NULL);
		close(pipefd[1]);
		read(pipefd[0], args->output, BUFFER_SIZE);
		close(pipefd[0]);
		dup2(1, STDOUT_FILENO);
	}
}

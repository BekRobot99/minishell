/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_part2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disilva <disilva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 22:01:32 by disilva           #+#    #+#             */
/*   Updated: 2024/08/20 22:12:02 by disilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	execute_heredoc(int fd, char *delimiter, t_shell_config *envp, int exp_flag)
{
	char	*read_line;

	fd = open("obj/heredoc", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
		return (ft_putstr_fd(TERMINAL_NAME, STDERR_FILENO), -1);
	while (1)
	{
		read_line = readline("> ");
		if (!read_line)
			break ;
		if (ft_strncmp(read_line, delimiter, ft_strlen(delimiter)) == 0)
		{
			free_str(read_line);
			break ;
		}
		needs_expansion(envp, &read_line, &exp_flag);
		ft_putstr_fd(read_line, fd);
		ft_putstr_fd("\n", fd);
		free_str(read_line);
	}
	close(fd);
	fd = open("obj/heredoc", O_RDONLY);
	if (fd == -1)
		return (ft_putstr_fd(TERMINAL_NAME, STDERR_FILENO), -1);
	return (fd);
}

int	handle_input_heredoc(t_command_context *command_args, t_shell_config *info,
		int *i)
{
	int	j;

	j = 0;
	if (verify_fd_perm(*(command_args->input_line + *i + 1)) == 0)
		return (info->exit_cd = 1, 0);
	else if (verify_fd_type(*(command_args->input_line + *i + 1)) == 0)
		return (info->exit_cd = 126, 0);
	if (command_args->input_fd != STDIN_FILENO)
		close(command_args->input_fd);
	if (ft_strncmp(*(command_args->input_line + *i), "<", 2) == 0)
		command_args->input_fd = open(*(command_args->input_line + *i + 1),
				O_RDONLY);
	if (ft_strncmp(*(command_args->input_line + *i), "<<", 2) == 0)
		command_args->input_fd = execute_heredoc(command_args->input_fd,
				*(command_args->input_line + *i + 1), info, j);
	if (command_args->input_fd == -1)
		return (ft_putstr_fd(TERMINAL_NAME, STDERR_FILENO),
			info->exit_cd = 1, 0);
	return (remove_elements(command_args->input_line, i, 2), 1);
}

int	handle_redirections(t_shell_config *info)
{
	int					i;
	t_command_context	*vars;

	vars = info->command_list;
	while (vars)
	{
		i = -1;
		while (vars && (vars->input_line + ++i) && *(vars->input_line + i))
		{
			if (ft_strchr(*(vars->input_line + i), '>')
				&& ft_strlen(*(vars->input_line + i)) <= 2)
			{
				if (!handle_output_append(vars, &i))
					return (info->exit_cd = 1, 0);
			}
			else if (ft_strchr(*(vars->input_line + i), '<')
				&& ft_strlen(*(vars->input_line + i)) <= 2)
				if (!handle_input_heredoc(vars, info, &i))
					return (0);
		}
		vars = vars->next;
	}
	return (1);
}

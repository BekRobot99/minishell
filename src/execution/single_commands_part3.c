/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_commands_part3.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disilva <disilva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 21:43:52 by disilva           #+#    #+#             */
/*   Updated: 2024/08/21 02:57:14 by disilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	run_builtin(t_shell_config *info)
{
	if (ft_strncmp(info->command_list->input_line[0], "pwd",
			ft_strlen(info->command_list->input_line[0])) == 0)
		ft_pwd(info);
	else if (ft_strncmp(info->command_list->input_line[0], "cd",
			ft_strlen(info->command_list->input_line[0])) == 0)
		ft_cd(info);
	else if (ft_strncmp(info->command_list->input_line[0], "export",
			ft_strlen(info->command_list->input_line[0])) == 0)
		ft_export(info);
	else if (ft_strncmp(info->command_list->input_line[0], "echo",
			ft_strlen(info->command_list->input_line[0])) == 0)
		ft_echo(info, 1);
	else if (ft_strncmp(info->command_list->input_line[0], "env",
			ft_strlen(info->command_list->input_line[0])) == 0)
		ft_env(info);
	else if (ft_strncmp(info->command_list->input_line[0], "unset",
			ft_strlen(info->command_list->input_line[0])) == 0)
		ft_unset(info);
}

void	cleanup_fds(int *fd[], int length)
{
	int	i;

	i = 0;
	while (i < length)
	{
		free(fd[i]);
		i++;
	}
	free(fd);
}

void	ft_reset_io(t_shell_config *info, int ind)
{
	if (dup2(info->fds[ind][0], STDIN_FILENO) == -1)
		fatal_error("Dup2 failed for stdin");
	if (dup2(info->fds[ind][1], STDOUT_FILENO) == -1)
		fatal_error("Dup2 failed for stdout");
	close(info->fds[ind][0]);
	close(info->fds[ind][1]);
	cleanup_fds(info->fds, 2);
}

char	*resolve_path(t_shell_config *info, char *command_path)
{
	char	*result;
	char	*temp;
	char	*temp_input_path;
	int		i;

	temp = getcwd(NULL, 0);
	temp_input_path = malloc(ft_strlen(command_path));
	i = 0;
	while (command_path[++i] != '\0')
		temp_input_path[i - 1] = command_path[i];
	temp_input_path[i - 1] = '\0';
	result = ft_strjoin(temp, temp_input_path);
	free(temp);
	free(temp_input_path);
	if (access(result, F_OK | X_OK) == 0)
		return (free_str(command_path), result);
	print_error_message_exit(info->command_list->input_line[0], 2, info);
	free_str(command_path);
	return (free(result), NULL);
}

char	*get_env_var(t_shell_config *env_array, char *key)
{
	char	*value;
	int		ind;

	ind = 0;
	while (env_array->envp[ind] != NULL && ft_strncmp(env_array->envp[ind], key,
			ft_strlen(key)) != 0)
		ind++;
	if (env_array->envp[ind] == NULL)
		return (NULL);
	value = ft_strdup(env_array->envp[ind]);
	return (value);
}

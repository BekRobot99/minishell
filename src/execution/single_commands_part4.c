/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_commands_part4.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abekri <abekri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 21:44:31 by disilva           #+#    #+#             */
/*   Updated: 2024/08/21 03:06:18 by abekri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*check_access(t_shell_config *info, char *command_name)
{
	char	*result;

	result = ft_strdup(command_name);
	free_str(command_name);
	if (access(result, F_OK | X_OK) == 0)
		return (result);
	print_error_message_exit(info->command_list->input_line[0], 2, info);
	return (free(result), NULL);
}

char	*strip_path(char *full_path)
{
	int		index;
	int		temp_index;
	char	*stripped_path;

	index = 0;
	while (full_path[index] != '\0' && full_path[index] != '=')
		index++;
	stripped_path = malloc((ft_strlen(full_path) - index) + 1);
	if (!stripped_path)
		perror("find_path.c line 46");
	temp_index = 0;
	index++;
	while (full_path[index] != '\0')
		stripped_path[temp_index++] = full_path[index++];
	stripped_path[temp_index] = '\0';
	free_str(full_path);
	return (stripped_path);
}

char	*iterate_paths(t_shell_config *info, char *arg, char ***path_dirs)
{
	char	*path_s;
	char	*command;

	if (arg[0] == '/')
		return (check_access(info, arg));
	if (arg[0] == '.' && arg[1] == '/' && arg[1] != '\0')
		return (resolve_path(info, arg));
	path_s = get_env_var(info, "PATH");
	if (!path_s)
	{
		free_str(path_s);
		print_error_message_exit(info->command_list->input_line[0], 2, info);
		return (NULL);
	}
	*path_dirs = ft_split(path_s, ':');
	free_str(path_s);
	(*path_dirs)[0] = strip_path((*path_dirs)[0]);
	command = ft_strjoin("/", arg);
	return (command);
}

char	*transform_into_path(char **path_2d, char *arg)
{
	char	*command;

	path_2d[0] = strip_path(path_2d[0]);
	command = ft_strjoin("/", arg);
	return (command);
}

char	*find_exec_path(t_shell_config *mini, char *arg, int i)
{
	char	*path_s;
	char	**path_2d;
	char	*command;

	if (arg[0] == '/')
		return (check_access(mini, arg));
	if (arg[0] == '.' && arg[1] == '/' && arg[1] != '\0')
		return (resolve_path(mini, arg));
	path_s = get_env_var(mini, "PATH");
	if (!path_s)
		return (free_str(path_s), free_str(arg),
			print_error_message_exit(mini->command_list->input_line[0],
				2, mini), NULL);
	path_2d = ft_split(path_s, ':');
	free_str(path_s);
	command = transform_into_path(path_2d, arg);
	i = -1;
	while (path_2d[++i] != NULL)
	{
		path_s = ft_strjoin(path_2d[i], command);
		if (access(path_s, F_OK | X_OK) == 0)
			return (free_str(command), free_2d_array(path_2d), path_s);
		free_str(path_s);
	}
	return (free_str(command), free_2d_array(path_2d), arg);
}

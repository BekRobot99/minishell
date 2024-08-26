/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_term_part2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disilva <disilva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 21:57:09 by disilva           #+#    #+#             */
/*   Updated: 2024/08/20 22:13:25 by disilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*shorten_node(char *node)
{
	char	**parts;
	char	*node_short;

	parts = ft_split(node, '.');
	node_short = ft_strdup(parts[0]);
	free_2d_array(parts);
	return (node_short);
}

char	*clean_directory_name(char *path)
{
	char	*current_dir;
	char	*dir_name;

	current_dir = ft_strdup(ft_strrchr(path, '/') + 1);
	if (ft_strchr(current_dir, '\n'))
	{
		dir_name = ft_substr(current_dir, 0, ft_strlen(current_dir) - 1);
	}
	else
	{
		dir_name = ft_strdup(current_dir);
	}
	free_str(current_dir);
	return (dir_name);
}

char	*construct_output(char *node_short, char *dir_name, char *user)
{
	char	*output;

	output = ft_strdup(node_short);
	free_str(node_short);
	output = ft_strjoin(output, ":");
	output = ft_strjoin(output, dir_name);
	free_str(dir_name);
	output = ft_strjoin(output, " ");
	output = ft_strjoin(output, user);
	free_str(user);
	output = ft_strjoin(output, "$ ");
	return (output);
}

char	*format_prompt(char *user, char *node, char *path)
{
	char	*node_short;
	char	*dir_name;
	char	*output;

	node_short = shorten_node(node);
	dir_name = clean_directory_name(path);
	output = construct_output(node_short, dir_name, user);
	free_str(path);
	return (output);
}

char	*format_iterm(char **environment)
{
	t_token_etw	param_cmd;
	char		*user;
	char		*current_dir;
	char		*node;

	(void)environment;
	params_start(&param_cmd, "/bin/hostname");
	perform_child_process_and_store_output(&param_cmd);
	current_dir = ft_strdup(param_cmd.output);
	get_args_empty(&param_cmd);
	params_start(&param_cmd, "/bin/pwd");
	perform_child_process_and_store_output(&param_cmd);
	node = ft_strdup(param_cmd.output);
	get_args_empty(&param_cmd);
	user = ft_strdup(environment[find_var_index(environment, "USER")]);
	return (format_prompt(user, current_dir, node));
}

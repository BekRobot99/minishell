/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disilva <disilva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 17:59:35 by disilva           #+#    #+#             */
/*   Updated: 2024/08/20 22:02:59 by disilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	*prepare_tilda_path(t_shell_config *env_vars)
{
	char	*temp;
	char	*home;
	char	*path;

	home = build_home_dir(env_vars, NULL);
	temp = remove_tilda_from_path(env_vars->command_list->input_line[1]);
	path = ft_strjoin(home, temp);
	free_str(home);
	free_str(temp);
	return (path);
}

void	change_to_tilda_path(t_shell_config *env_vars)
{
	char	*cwd;
	char	*path;

	cwd = getcwd(NULL, 0);
	path = prepare_tilda_path(env_vars);
	if (access(path, F_OK | X_OK) == 0)
	{
		update_old_env_variable(env_vars, cwd);
		chdir(path);
		update_new_path(env_vars, path);
		env_vars->exit_cd = 0;
	}
	else
	{
		print_error_message_extra("cd: ",
			env_vars->command_list->input_line[1], 2,
			env_vars);
	}
	free_str(cwd);
	free_str(path);
}

void	change_to_prev_dir(t_shell_config *mini)
{
	char	*cwd;
	char	*furture_wd;
	int		furture_wd_size;
	int		i;

	cwd = getcwd(NULL, 0);
	furture_wd_size = get_prev_dir_len(cwd);
	furture_wd = malloc(furture_wd_size + 1);
	i = -1;
	while (++i < furture_wd_size)
		furture_wd[i] = cwd[i];
	furture_wd[i] = '\0';
	update_old_env_variable(mini, cwd);
	chdir(furture_wd);
	free_str(furture_wd);
	mini->exit_cd = 0;
}

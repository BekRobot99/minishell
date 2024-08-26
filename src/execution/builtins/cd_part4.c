/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_part4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disilva <disilva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 21:41:09 by disilva           #+#    #+#             */
/*   Updated: 2024/08/21 00:22:40 by disilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	*build_home_dir(t_shell_config *mini, char *future_wd)
{
	char	*home;
	int		i;
	int		j;

	home = get_env_var(mini, "HOME");
	if (!home)
		home = mini->home;
	else
		home = strip_path(home);
	i = ft_strlen(home);
	while (i > -1 && home[i] != '=')
		i--;
	future_wd = malloc(ft_strlen(home) - i);
	j = -1;
	while (home[++i] != '\0')
		future_wd[++j] = home[i];
	future_wd[++j] = '\0';
	free(home);
	return (future_wd);
}

void	change_to_previous_dir_from_env(t_shell_config *mini)
{
	char	*oldpwd;
	char	*cwd;

	if (!find_minus_in_envp(mini->envp, "OLDPWD"))
		return (print_error_message(mini->command_list->input_line[0], NULL, 3,
				mini));
	cwd = getcwd(NULL, 0);
	oldpwd = get_env_var(mini, "OLDPWD=");
	oldpwd = strip_path(oldpwd);
	update_old_env_variable(mini, cwd);
	chdir(oldpwd);
	update_new_path(mini, oldpwd);
	ft_putendl_fd(oldpwd, mini->out_fd);
	mini->exit_cd = 0;
}

void	ft_cd_other_cases(t_shell_config *info)
{
	if (info->command_list->input_line[1]
		&& ft_strncmp(info->command_list->input_line[1], "/Users/", 7) != 0)
		return (change_to_rel_path(info), update_new_path(info, getcwd(NULL,
					0)));
	else
		print_error_message_extra("cd: ", info->command_list->input_line[1], 2,
			info);
}

void	ft_cd(t_shell_config *info)
{
	if (ft_strncmp(info->command_list->input_line[0], "cd", 3) != 0)
		print_error_message_exit(info->command_list->input_line[0], 1, info);
	else if (info->command_list->input_line[1]
		&& ((ft_strncmp(info->command_list->input_line[1], "..", 2) == 0
				&& ft_strlen(info->command_list->input_line[1]) == 2)))
		return (change_to_prev_dir(info), update_new_path(info, getcwd(NULL,
					0)));
	else if (info->command_list->input_line[1]
		&& ft_strncmp(info->command_list->input_line[1], "-", 1) == 0)
		return (change_to_previous_dir_from_env(info));
	else if (!info->command_list->input_line[1]
		|| ft_strncmp(info->command_list->input_line[1], "~", 2) == 0
		|| ft_strncmp(info->command_list->input_line[1], ";", 2) == 0)
		return (change_to_home_dir(info), update_new_path(info, getcwd(NULL,
					0)));
	else if (info->command_list->input_line[1]
		&& ft_strncmp(info->command_list->input_line[1], "~/", 2) == 0)
		return (change_to_tilda_path(info), update_new_path(info, getcwd(NULL,
					0)));
	else if (info->command_list->input_line[1]
		&& ft_strncmp(info->command_list->input_line[1], "/", 1) == 0)
		return (change_to_abs_path(info), update_new_path(info, getcwd(NULL,
					0)));
	ft_cd_other_cases(info);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_part2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disilva <disilva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 21:40:04 by disilva           #+#    #+#             */
/*   Updated: 2024/08/20 23:20:09 by disilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	change_to_rel_path(t_shell_config *mini)
{
	char	*temp;
	char	*cwd;
	char	*furture_wd;

	cwd = getcwd(NULL, 0);
	temp = ft_strjoin(cwd, "/");
	furture_wd = ft_strjoin(temp, mini->command_list->input_line[1]);
	if (access(furture_wd, F_OK | X_OK) == 0)
	{
		update_old_env_variable(mini, cwd);
		chdir(furture_wd);
		mini->exit_cd = 0;
	}
	else
	{
		print_error_message_extra("cd: ", mini->command_list->input_line[1], 2,
			mini);
	}
	free_str(temp);
	free_str(furture_wd);
}

void	change_to_abs_path(t_shell_config *mini)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (access(mini->command_list->input_line[1], F_OK | X_OK) == 0)
	{
		update_old_env_variable(mini, cwd);
		chdir(mini->command_list->input_line[1]);
		mini->exit_cd = 0;
	}
	else
		print_error_message_extra("cd: ", mini->command_list->input_line[1], 2,
			mini);
}

void	change_to_home_dir(t_shell_config *env_vars)
{
	char	*future_wd;
	char	*cwd;

	if (!find_var_index(env_vars->envp, "HOME")
		&& env_vars->command_list->input_line[1] == NULL)
	{
		print_error_message_exit("cd", 4, env_vars);
		return ;
	}
	future_wd = NULL;
	cwd = getcwd(NULL, 0);
	future_wd = get_env_var(env_vars, future_wd);
	if (ft_strlen(env_vars->command_list->input_line[0]) == 2)
	{
		update_old_env_variable(env_vars, cwd);
		chdir(future_wd);
		env_vars->exit_cd = 0;
	}
	else
		print_error_message_exit(env_vars->command_list->input_line[0], 1,
			env_vars);
	free_str(future_wd);
}

int	get_prev_dir_len(char *cwd)
{
	int	i;

	i = ft_strlen(cwd) - 1;
	while (--i > -1)
		if (cwd[i] == '/')
			break ;
	if (i == 0)
		return (1);
	return (i);
}

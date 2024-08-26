/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_minishell_part2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disilva <disilva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 21:55:02 by disilva           #+#    #+#             */
/*   Updated: 2024/08/20 22:13:33 by disilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	add_missing_vars(t_shell_config *mini_env, int *index)
{
	if (!find_var_index(mini_env->envp, "PWD"))
	{
		mini_env->envp[(*index)++] = ft_strjoin("PWD=", getcwd(NULL, 0));
	}
	if (!find_var_index(mini_env->envp, "OLDPWD"))
	{
		mini_env->envp[(*index)++] = ft_strdup("OLDPWD");
	}
	if (!find_var_index(mini_env->envp, "SHLVL"))
	{
		mini_env->envp[(*index)++] = ft_strdup("SHLVL=1");
		mini_env->envp[*index] = NULL;
	}
	else
	{
		adjust_shell_lvl(mini_env, 1);
		mini_env->envp[*index] = NULL;
	}
}

void	setup_env(char *orig_env[], int i, t_shell_config *mini_env, int count)
{
	while (orig_env[++i] && i < count)
	{
		copy_env_var(orig_env, i, mini_env);
	}
	add_missing_vars(mini_env, &i);
}

void	init_env(char **env, int count, t_shell_config *mini_env)
{
	int	index;

	index = -1;
	if (!is_var_set(env, "PWD"))
		count += 1;
	if (!is_var_set(env, "OLDPWD"))
		count += 1;
	if (!is_var_set(env, "SHLVL"))
		count += 1;
	mini_env->envp = (char **)malloc(sizeof(char *) * count + 2);
	if (!mini_env->envp)
		return (printf("Error: malloc failed\n"), finalize(mini_env),
			exit(1));
	setup_env(env, index, mini_env, count);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disilva <disilva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 06:34:42 by abekri            #+#    #+#             */
/*   Updated: 2024/08/20 23:09:37 by disilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_var_set(char **env, char *var)
{
	int		i;

	i = 0;
	while (env[i] != NULL && ft_strncmp(env[i], var,
			ft_strlen(var)) != 0)
		i++;
	if (*env == NULL)
		return (0);
	return (1);
}

int	find_var_index(char **env, char *var)
{
	int	i;

	i = -1;
	while (env[++i] != NULL)
	{
		if (ft_strncmp(env[i], var, ft_strlen(var)) == 0
			&& (env[i][ft_strlen(var)] == '='
			|| env[i][ft_strlen(var)] == '\0'
				|| (env[i][ft_strlen(var)] == '+' && env[i][ft_strlen(var)
					+ 1] == '=')))
			return (i);
	}
	return (0);
}

int	has_prefix(char *env[], char *s)
{
	int	i;

	i = -1;
	while (env[++i])
	{
		if (ft_strncmp(env[i], s, ft_strlen(s)) == 0)
			return (1);
	}
	return (0);
}

void	copy_env_var(char *orig_env[], int index, t_shell_config *mini_env)
{
	if (has_prefix(orig_env, "OLDPWD=")
		&& ft_strncmp(orig_env[index], "OLDPWD", 6) == 0)
	{
		mini_env->envp[index] = ft_strdup("OLDPWD");
	}
	else
		mini_env->envp[index] = ft_strdup(orig_env[index]);
}

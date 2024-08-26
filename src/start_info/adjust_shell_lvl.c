/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adjust_shell_lvl.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disilva <disilva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 04:23:02 by abekri            #+#    #+#             */
/*   Updated: 2024/08/20 22:13:22 by disilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_shell(t_shell_config *env, char *prev_shell,
		char *next_shell)
{
	int	i;

	i = -1;
	while (env->envp[++i])
	{
		if (ft_strncmp(env->envp[i], "SHLVL=", ft_strlen("SHLVL=")) == 0)
		{
			free_str(env->envp[i]);
			env->envp[i] = ft_strdup(prev_shell);
			break ;
		}
	}
	free_str(next_shell);
	free_str(prev_shell);
}

int	extract_value(char *s)
{
	int	i;
	int	level;

	i = -1;
	level = 0;
	while (s[++i])
	{
		if (!(s[i] >= '0' && s[i] <= '9'))
			level = 1;
		if (ft_isalpha(s[i]))
		{
			level = 2;
			break ;
		}
	}
	return (level);
}

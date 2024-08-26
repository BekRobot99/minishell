/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adjust_shell_lvl_part3.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disilva <disilva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 22:00:05 by disilva           #+#    #+#             */
/*   Updated: 2024/08/20 23:22:19 by disilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*calculate_next_shell_level(char *prev_shell, int increment)
{
	char	*next_shell;

	if (extract_value(prev_shell) == 1)
		next_shell = ft_strdup("0");
	else if (extract_value(prev_shell) == 2)
		next_shell = ft_strdup("1");
	else
	{
		if (increment == 0)
		{
			next_shell = ft_itoa(ft_atoi(prev_shell) - 1);
			if (ft_atoi(next_shell) < 0)
				next_shell = ft_strdup("0");
		}
		else if (increment == 1)
			next_shell = ft_itoa(ft_atoi(prev_shell) + 1);
		else
			next_shell = ft_strdup("1");
	}
	return (next_shell);
}

void	update_shell_level(t_shell_config *env,
		char *prev_shell, char *next_shell)
{
	free_str(prev_shell);
	prev_shell = ft_strjoin("SHLVL=", next_shell);
	free_shell(env, prev_shell, next_shell);
}

void	adjust_shell_lvl(t_shell_config *env, int increment)
{
	char	*prev_shell;
	char	*next_shell;

	prev_shell = get_old_shell_level(get_env_var(env, "SHLVL"));
	if (!prev_shell)
		return ;
	next_shell = calculate_next_shell_level(prev_shell, increment);
	update_shell_level(env, prev_shell, next_shell);
}

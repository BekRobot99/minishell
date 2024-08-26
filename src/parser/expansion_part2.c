/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_part2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disilva <disilva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 22:07:43 by disilva           #+#    #+#             */
/*   Updated: 2024/08/20 21:00:10 by disilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_str(char *str)
{
	if (str != NULL)
		free(str);
	str = NULL;
}

int	check_valid_env_char(int str)
{
	int	env;

	env = 1;
	if (!(str >= '0' && str <= '9') && !((str >= 'A' && str <= 'Z')
			|| (str >= 'a' && str <= 'z')) && str != '_')
	{
		env = 0;
	}
	return (env);
}

int	handle_exit_status(int exit_code, int *i, char **expanded_str)
{
	char	*exit_status;

	(*i)++;
	exit_status = ft_itoa(exit_code);
	if (!exit_status)
		return (0);
	*expanded_str = ft_strncat(*expanded_str, exit_status,
			ft_strlen(exit_status));
	if (!*expanded_str)
		return (free_str(exit_status), --(*i), 0);
	return (free_str(exit_status), --(*i), 1);
}

int	needs_expansion(t_shell_config *envp, char **arg, int *exp_flag)
{
	char	*expanded_str;
	char	*argm;

	expanded_str = NULL;
	argm = *arg;
	if (successful_expansion(envp, argm, &expanded_str, exp_flag))
	{
		free_str(argm);
		*arg = expanded_str;
		return (1);
	}
	return (0);
}

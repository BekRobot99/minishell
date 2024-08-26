/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disilva <disilva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 02:00:04 by abekri            #+#    #+#             */
/*   Updated: 2024/08/20 22:11:46 by disilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	expand_variable(t_shell_config *args, char *envp, int *i,
		char **expanded_str)
{
	if ((envp + ++(*i)) && (ft_strncmp((envp + *i), "?", 1) == 0
			|| ft_strncmp((envp + *i), "$", 1) == 0))
	{
		if (ft_strncmp((envp + *i), "?", 1) == 0)
		{
			if (!handle_exit_status(args->exit_cd, i, expanded_str))
				return (0);
		}
		else if (ft_strncmp((envp + *i), "$", 1) == 0)
		{
			if (!handle_exit_status(95394, i, expanded_str))
				return (0);
		}
	}
	else
	{
		if (!handle_env_variable(args, envp, i, expanded_str))
			return ((*i)--, 0);
	}
	return (1);
}

char	*handle_single_quotes(char *arg, int *i, char **expanded_str)
{
	int	start;
	int	end;

	start = ++(*i);
	if (ft_strncmp((arg + *i), "'", 1) == 0)
		return ((*i)++, NULL);
	while (*(arg + *i) && ft_strncmp((arg + *i), "'", 1) != 0)
	{
		(*i)++;
		end = *i;
	}
	(*i)++;
	*expanded_str = ft_strncat(*expanded_str, (arg + start), (end - start));
	return (*expanded_str);
}

char	*handle_double_quotes(t_shell_config *envp, char *arg, int *i,
		char **expanded_str)
{
	while (*(arg + ++(*i)) && ft_strncmp((arg + *i), "\"", 1) != 0)
	{
		if (ft_strncmp((arg + *i), "$", 1) == 0 && ft_strncmp((arg + (*i) + 1),
				" ", 1) != 0 && ft_strncmp((arg + (*i) + 1), "\"", 1) != 0)
			expand_variable(envp, arg, i, expanded_str);
		else
			*expanded_str = ft_strncat(*expanded_str, (arg + *i), 1);
	}
	return ((*i)++, *expanded_str);
}

char	*successful_expansion(t_shell_config *envp, char *arg,
		char **expanded_str, int *exp_flag)
{
	int	i;

	i = 0;
	while (*(arg + i))
	{
		if (ft_strncmp((arg + i), "'", 1) == 0)
			handle_single_quotes(arg, &i, expanded_str);
		else if (ft_strncmp((arg + i), "\"", 1) == 0)
			handle_double_quotes(envp, arg, &i, expanded_str);
		else if (ft_strncmp((arg + i), "$", 1) == 0 && *(arg + i + 1) != '\0')
		{
			if (expand_variable(envp, arg, &i, expanded_str))
				*exp_flag = 1;
			i++;
		}
		else
			*expanded_str = ft_strncat(*expanded_str, (arg + i++), 1);
	}
	return (*expanded_str);
}

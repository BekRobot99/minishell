/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_part4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disilva <disilva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 00:50:16 by disilva           #+#    #+#             */
/*   Updated: 2024/08/20 23:25:45 by disilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static void	ft_duplicate_env_vars(char **envp, char **sorted_vars)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		sorted_vars[i] = strdup(envp[i]);
		i++;
	}
	sorted_vars[i] = NULL;
}

static void	ft_swap_vars(char **var1, char **var2)
{
	char	*temp;

	temp = *var1;
	*var1 = *var2;
	*var2 = temp;
}

static void	ft_sort_vars(char **sorted_vars)
{
	int	i;
	int	j;

	i = 0;
	while (sorted_vars[i] != NULL)
	{
		j = 0;
		while (sorted_vars[j + 1] != NULL)
		{
			if (ft_strncmp(sorted_vars[j], sorted_vars[j + 1],
					ft_strlen(sorted_vars[j + 1])) < 0)
			{
				ft_swap_vars(&sorted_vars[j], &sorted_vars[j + 1]);
			}
			j++;
		}
		i++;
	}
}

char	**ft_sort_env_vars(char **envp, char **sorted_vars)
{
	ft_duplicate_env_vars(envp, sorted_vars);
	ft_sort_vars(sorted_vars);
	return (sorted_vars);
}

int	ft_calculate_export_exit_status(t_shell_config	*info)
{
	int	i;

	if (info->command_list->input_line[1][0] == '-')
		return (2);
	i = 0;
	while (info->command_list->input_line[++i] != NULL)
	{
		if (ft_isdigit(info->command_list->input_line[i][0]) == 1)
			return (1);
		else if (!ft_check_export_string(info->command_list->input_line[i]))
			return (1);
	}
	return (0);
}

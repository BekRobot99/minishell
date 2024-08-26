/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_part2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disilva <disilva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 00:50:27 by disilva           #+#    #+#             */
/*   Updated: 2024/08/20 23:41:56 by disilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	add_new_env_var(t_shell_config *input, int *i, int j)
{
	if (ft_strnstr(input->command_list->input_line[j], "+=",
			ft_strlen(input->command_list->input_line[j])) != NULL)
	{
		ft_add_plus_minus(input->envp, *i, input->command_list->input_line[j]);
	}
	else
	{
		input->envp[(*i)] = ft_strdup(input->command_list->input_line[j]);
	}
	(*i)++;
	input->envp[(*i)] = NULL;
}

void	export_no_args(t_shell_config *input)
{
	char	**alpha_order;
	int		i;

	alpha_order = malloc((count_env_vars(input->envp) + 1) * sizeof(char *));
	alpha_order = ft_sort_env_vars(input->envp, alpha_order);
	i = count_env_vars(alpha_order);
	while (--i > -1)
	{
		if (ft_strchr(alpha_order[i], '=') != NULL
			&& ft_strlen(alpha_order[i]) != 0)
			print_export_without_args(input, alpha_order, i, 1);
		else if (ft_strlen(alpha_order[i]) != 0)
			print_export_without_args(input, alpha_order, i, 2);
	}
	free_2d_array(alpha_order);
}

static void	resize_envp_array(t_shell_config *input, int *args)
{
	char	**new_envp;
	int		new_envp_size;

	new_envp_size = count_env_vars(input->envp)
		+ count_env_vars(input->command_list->input_line);
	new_envp = ft_calloc((new_envp_size), sizeof(char *));
	while (input->envp[++(*args)] != NULL)
		new_envp[*args] = ft_strdup(input->envp[*args]);
	free_2d_array(input->envp);
	input->envp = ft_calloc((new_envp_size), sizeof(char *));
	*args = -1;
	while (new_envp[++(*args)] != NULL)
		input->envp[*args] = ft_strdup(new_envp[*args]);
	input->envp[new_envp_size] = NULL;
	free_2d_array(new_envp);
}

void	update_env_with_args(t_shell_config *input, char *envp, int *i, int j)
{
	if (!find_var_index(input->envp, envp))
	{
		add_new_env_var(input, i, j);
	}
	else
	{
		update_existing_env_var(input, envp, j);
	}
}

void	update_envp_size(t_shell_config *info, int envp, int args)
{
	char	*var;

	resize_envp_array(info, &envp);
	while (info->command_list->input_line[++args] != NULL)
	{
		if (handle_export_errors(info, args) == 0)
			continue ;
		var = extract_env_var_name(info->command_list->input_line[args]);
		update_env_with_args(info, var, &envp, args);
		free_str(var);
	}
}

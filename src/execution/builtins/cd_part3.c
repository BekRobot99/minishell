/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_part3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disilva <disilva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 21:40:41 by disilva           #+#    #+#             */
/*   Updated: 2024/08/20 22:02:08 by disilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	*remove_tilda_from_path(char *s)
{
	char	*result;
	int		i;
	int		j;

	result = malloc(ft_strlen(s));
	i = 0;
	j = -1;
	while (++i < (int)ft_strlen(s) && ++j < i)
		result[j] = s[i];
	result[i] = '\0';
	return (result);
}

void	update_oldpwd_value(t_shell_config *envp, char *owd, int index)
{
	free_str(envp->envp[index]);
	envp->envp[index] = NULL;
	envp->envp[index] = ft_strjoin("OLDPWD=", owd);
	free_str(owd);
}

void	update_old_env_variable(t_shell_config *envp, char *owd)
{
	int	i;

	i = find_minus_in_envp(envp->envp, "OLDPWD");
	if (i > 0)
	{
		update_oldpwd_value(envp, owd, i);
	}
	else
	{
		i = 0;
		while (envp->envp[i] != NULL && ft_strncmp(envp->envp[i], "OLDPWD",
				7) != 0)
			i++;
		free_str(envp->envp[i]);
		envp->envp[i] = NULL;
		envp->envp[i] = ft_strjoin("OLDPWD=", owd);
		free_str(owd);
	}
}

void	update_new_path(t_shell_config *envp, char *pwd)
{
	int	i;

	i = 0;
	if (envp->command_list->input_line[1]
		== NULL && !find_var_index(envp->envp, "HOME"))
		return ;
	if (find_var_index(envp->envp, "PWD"))
	{
		while (envp->envp[i] != NULL && ft_strncmp(envp->envp[i], "PWD",
				3) != 0)
			i++;
		free_str(envp->envp[i]);
		envp->envp[i] = ft_strjoin("PWD=", pwd);
		free_str(pwd);
	}
	else
	{
		while (envp->envp[i] != NULL && ft_strncmp(envp->envp[i], "PWD",
				3) != 0)
			i++;
		free_str(envp->envp[i]);
		envp->envp[i] = ft_strjoin("PWD=", pwd);
		envp->envp[i + 1] = NULL;
		free_str(pwd);
	}
}

int	find_minus_in_envp(char **envp, char *var)
{
	int	i;

	i = -1;
	while (envp[++i] != NULL)
	{
		if (ft_strncmp(envp[i], var, ft_strlen(var)) == 0
			&& envp[i][ft_strlen(var)] == '=')
			return (i);
	}
	return (0);
}

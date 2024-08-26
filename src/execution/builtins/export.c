/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disilva <disilva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 17:59:11 by disilva           #+#    #+#             */
/*   Updated: 2024/08/20 23:25:05 by disilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	ft_replace_env_var(char **envp, char *replace, char *var)
{
	int	i;

	i = -1;
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], replace, ft_strlen(var)) == 0)
		{
			free_str(envp[i]);
			envp[i] = ft_strdup(var);
			break ;
		}
	}
}

void	ft_add_plus_minus(char **envp, int i, char *to_add)
{
	char	*result;
	int		j;
	int		k;

	j = -1;
	k = -1;
	result = malloc(ft_strlen(to_add));
	while (to_add[++j] != '\0')
		if (to_add[j] != '+')
			result[++k] = to_add[j];
	result[++k] = '\0';
	envp[i] = result;
}

static char	*concat_and_append(const char *var, const char *to_add)
{
	char	*result;
	char	*tmp;
	int		j;
	int		k;

	tmp = ft_strjoin(var, "=");
	result = ft_calloc(ft_strlen(tmp) + ft_get_append_length(to_add) + 1, 1);
	j = 0;
	k = 0;
	while (tmp[j] != '\0')
		result[k++] = tmp[j++];
	j = 0;
	while (to_add[j] != '\0' && to_add[j] != '=')
		j++;
	j++;
	while (to_add[j] != '\0')
		result[k++] = to_add[j++];
	result[k] = '\0';
	free_str(tmp);
	return (result);
}

static void	update_env_variable(char **envp, int *i, const char *var,
		const char *to_add)
{
	char	*result;

	while (envp[++(*i)] != NULL)
	{
		if (ft_strncmp(envp[*i], var, ft_strlen(var)) == 0)
		{
			result = concat_and_append(var, to_add);
			free_str(envp[*i]);
			envp[*i] = result;
			return ;
		}
	}
}

void	ft_append_to_env_var_ex(char **envp, int i, char *to_add, char *var)
{
	update_env_variable(envp, &i, var, to_add);
}

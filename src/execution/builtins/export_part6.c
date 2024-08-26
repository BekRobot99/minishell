/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_part6.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disilva <disilva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 23:25:11 by disilva           #+#    #+#             */
/*   Updated: 2024/08/20 23:34:45 by disilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	ft_get_append_length(const char *s)
{
	int	j;
	int	k;

	j = 0;
	while (s[j] != '\0' && s[j] != '=')
		j++;
	k = 0;
	while (s[++j] != '\0')
		k++;
	return (k);
}

void	ft_append_to_env_var(char **envp, int i, char *to_add, char *var)
{
	char	*result;
	int		j;
	int		k;

	while (envp[++i] != NULL)
		if (ft_strncmp(envp[i], var, ft_strlen(var)) == 0)
			break ;
	result = ft_calloc(ft_strlen(envp[i]) + ft_get_append_length(to_add) + 1,
			1);
	k = -1;
	j = -1;
	while (envp[i][++j] != '\0')
		result[++k] = envp[i][j];
	j = 0;
	while (to_add[j] != '\0' && to_add[j] != '=')
		j++;
	while (to_add[++j] != '\0')
		result[++k] = to_add[j];
	result[++k] = '\0';
	free_str(envp[i]);
	envp[i] = NULL;
	envp[i] = result;
}

int	ft_has_value_after_equal(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] != '\0' && arg[i] != '=')
		i++;
	if (arg[i] == '\0')
		return (0);
	return (1);
}

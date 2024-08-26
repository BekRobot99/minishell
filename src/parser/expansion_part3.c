/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_part3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disilva <disilva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 22:07:50 by disilva           #+#    #+#             */
/*   Updated: 2024/08/20 23:20:58 by disilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*extract_env_value(char **var_env_names, char *var_name)
{
	int	var_len;
	int	index;

	var_len = ft_strlen(var_name);
	index = 0;
	while (var_env_names && (var_env_names + index) && *(var_env_names + index))
	{
		if (ft_strncmp(*(var_env_names + index), var_name, var_len) == 0
			&& *(*(var_env_names + index) + var_len) == '=')
			return (ft_substr((*(var_env_names + index) + var_len + 1), 0,
					ft_strlen((*(var_env_names + index) + var_len + 1))));
		index++;
	}
	return (NULL);
}

char	*ft_strncat(char *s1, char *s2, int n)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	if (!s1 && !s2)
		return (NULL);
	str = (char *)malloc((ft_strlen(s1) + n + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (s1 && *(s1 + i) != '\0')
	{
		*(str + i) = *(s1 + i);
		i++;
	}
	j = -1;
	while (++j < n && s2 && *(s2 + j) != '\0')
		*(str + i + j) = *(s2 + j);
	*(str + i + j) = '\0';
	return (free_str(s1), str);
}

char	*extract_env_var_name(char *env_line)
{
	char	*var;
	int		i;

	i = 0;
	while (env_line[i] != '\0' && env_line[i] != '+' && env_line[i] != '=')
		i++;
	var = malloc(i);
	i = -1;
	while (env_line[++i] != '\0' && env_line[i] != '+' && env_line[i] != '=')
		var[i] = env_line[i];
	var[i] = '\0';
	return (var);
}

int	handle_env_variable(t_shell_config *envp, char *args, int *i,
		char **expanded_str)
{
	char	*env_var;
	char	*env_value;
	int		start;
	int		end;

	start = *i;
	env_value = NULL;
	env_var = NULL;
	while (*(args + *i) && check_valid_env_char(*(args + *i)))
		(*i)++;
	end = *i;
	env_var = ft_substr(args, start, (end - start));
	if (!env_var)
		return (0);
	env_value = extract_env_value(envp->envp, env_var);
	if (!env_value)
		return (free_str(env_var), 0);
	*expanded_str = ft_strncat(*expanded_str, env_value, ft_strlen(env_value));
	if (!*expanded_str)
		return (free_str(env_var), free_str(env_value),
			--(*i), 0);
	return (free_str(env_var), free_str(env_value),
		--(*i), 1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_minishell_part3.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disilva <disilva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 21:56:06 by disilva           #+#    #+#             */
/*   Updated: 2024/08/20 22:13:39 by disilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	count_env_vars(char **env)
{
	int	len;

	len = -1;
	while (env && env[++len])
		;
	return (len);
}

char	*get_cwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		return (ft_strdup(""));
	return (cwd);
}

char	*get_home(void)
{
	char	*cwd;
	char	*home;
	char	**parts;
	char	*tmp;

	home = getcwd(NULL, 0);
	if (home == NULL)
		return (ft_strdup(""));
	parts = ft_split(home, '/');
	tmp = ft_strdup("/");
	cwd = ft_strjoin(tmp, parts[0]);
	free(tmp);
	tmp = ft_strjoin(cwd, "/");
	free(cwd);
	cwd = ft_strjoin(tmp, parts[1]);
	free_str(tmp);
	free_2d_array(parts);
	if (cwd == NULL)
		return (free_str(home), ft_strdup(""));
	free_str(home);
	return (cwd);
}

void	start_info_ms(t_shell_config *term_name, char **mini_env)
{
	int		len;
	char	*path;
	char	*home;
	int		exit_code;

	len = count_env_vars(mini_env);
	init_env(mini_env, len, term_name);
	exit_code = term_name->exit_cd;
	exit_code = 0;
	term_name->out_fd = STDOUT_FILENO;
	term_name->in_fd = STDIN_FILENO;
	path = term_name->pwd;
	home = term_name->home;
	path = get_cwd();
	home = get_home();
	if (DEBUG)
	{
		print_2d_array(term_name->envp, "ENVIRONMENT VARIABLES");
		term_name->terminal_name = format_iterm(term_name->envp);
	}
	else
		term_name->terminal_name = ft_strdup("minishell-0.1$ ");
}

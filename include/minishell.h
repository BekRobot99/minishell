/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disilva <disilva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 22:46:11 by abekri            #+#    #+#             */
/*   Updated: 2024/08/20 23:36:57 by disilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <termios.h>
# define MAX_TOKENS 1000
# define ERR_SYNTX_MSG "Syntax error near token: %c\n"
# define ERR_SYNTX_MSG_RE_H "Syntax error: expected %s before end of line\n"
# define ERROR_EXPORT_MSG \
	"export: usage: export [-nf]\
[name[=value] ...] or export -p"
# define MAX_COMMANDS 10
# define MAX_ENV 50
# define BUFFER_SIZE 1024
# define DEBUG 0
# define TERMINAL_NAME "minishell"
# define MAX_ENV_VARS 1024
# define MAX_ARGS 128
# define MAX_STRING_LEN 256
# define MAX_LIST_SIZE 100

extern int	g_signal;

typedef enum e_error_cod
{
	CMD_NOT_EXEC = 126,
	ERR_SYNTX_COD = 258,
	CTRL_C = 130,
	CDM_NOT_EXIST = 127,
}								t_error_cod;

typedef enum s_type
{
	WORD,
	R_DIR_APPEND,
	H_DOC,
	ERR,
	EOL,
	PIPE = '|',
}								t_tokenize_type;

typedef struct t_command_context
{
	char						**input_line;
	struct t_command_context	*previous;
	char						*command_list;
	int							command_count;
	int							input_fd;
	int							output_fd;
	struct t_command_context	*next;
}						t_command_context;

typedef struct token_etw_s
{
	struct token_etw_s	*previous;
	struct token_etw_s	*next;
	char				*value;
	t_tokenize_type		kind;
	char				**cmd_args;
	char				*output;
}						t_token_etw;
typedef struct s_shell_config
{
	char				*terminal_name;
	char				*pwd;
	char				*home;
	int					exit_cd;
	char				**envp;
	pid_t				*var_pids;
	int					**fds;
	char				*readline;
	t_command_context	*command_list;
	t_token_etw			*token_list;
	int					out_fd;
	int					in_fd;
}						t_shell_config;

typedef struct s_analyse
{
	char				*read_line;
	int					position;
	int					isdouble_quote;
	int					is_single_quote;
}						t_analyse;

typedef struct redirections_hr_s
{
	int							arg_index;
	int							cmd_index;
}								t_redirections_hr;

typedef struct single_command_rp_s
{
	int							len;
	char						*result;
	char						*temp;
	char						*full_path;
}								t_single_command_rp;

typedef struct single_command_fep_s
{
	int							index;
	char						*path_str;
	char						**path_dirs;
	char						*command_path;
}								t_single_command_fep;

typedef struct single_command_esc_s
{
	char						*path;
	int							pid;
	int							**fds;
}								t_single_command_esc;

typedef struct multiple_commands_ecp_s
{
	char						*path;
	char						**cmds;
	char						**envp;
	int							**fds;
	int							lst_size;
}								t_multiple_commands_ecp;

typedef struct multiple_commands_emc_s
{
	int							lst_size;
	int							*pids;
	int							**fds;
	char						*exec_params[4];
}								t_multiple_commands_emc;

typedef struct echo_ptie_s
{
	int							out_fd;
	char						*home;
	char						*trimmed_home;
	char						*print;
	int							i;
	int							j;
}								t_echo_ptie;

typedef struct echo_ee_s
{
	int							out_fd;
	int							suppress_newline;
	int							i;
	int							*exit_code;
	int							no_flags;
}								t_echo_ee;

typedef struct export_ues_s
{
	char						**new_envp;
	int							new_envp_size;
	char						*var;
	int							i;
	int							j;
}								t_export_ues;

//builtins
void		change_to_rel_path(t_shell_config *envp);
void		change_to_abs_path(t_shell_config *envp);
void		change_to_home_dir(t_shell_config *env_vars);
int			get_prev_dir_len(char *cwd);
char		*extract_pwd(char *pwd);

char		*remove_tilda_from_path(char *s);
void		update_oldpwd_value(t_shell_config *envp, char *owd, int index);
void		update_old_env_variable(t_shell_config *envp, char *owd);
void		update_new_path(t_shell_config *envp, char *pwd);
int			find_minus_in_envp(char **envp, char *var);

char		*build_home_dir(t_shell_config *envp, char *future_wd);
void		change_to_previous_dir_from_env(t_shell_config *info);
void		ft_cd(t_shell_config *info);

int			check_in_envp(char **envp, const char *var);
char		*prepare_tilda_path(t_shell_config *env_vars);
void		change_to_tilda_path(t_shell_config *env_vars);
void		change_to_prev_dir(t_shell_config *envp);

int			s_echo_n_option(char *str);
void		print_newline(t_shell_config *info, int output);
char		*extract_home_path(char *home);
void		print_home_directory(t_shell_config *info);
void		print_echo_argument(t_shell_config *info, int increment);
void		process_echo_argument(t_shell_config *info,
				int *params, int *output, int i);
void		ft_echo(t_shell_config *info, int params);

void		ft_env(t_shell_config *info);

void		ft_exit(t_shell_config *info);
int			determine_exit_action(t_shell_config *info);
long long	string_to_long_long(const char *str);
void		terminate_shell(t_shell_config *env, int c);
int			is_numeric_string(char *str);
int			get_envp_length(char **envp);
void		print_export_without_args(t_shell_config *out_fd, char **entry,
				int key, int flag);
void		export_no_args(t_shell_config *input);
void		update_env_with_args(t_shell_config *input, char *envp,
				int *i, int j);
void		update_envp_size(t_shell_config *info, int envp, int args);
void		ft_export(t_shell_config *info);

int			ft_find_in_envp(char **envp, char *var);
int			handle_export_errors(t_shell_config *input, int i);
char		*extract_env_var_name(char *env_line);

char		**ft_sort_env_vars(char **envp, char **sorted_vars);
int			ft_calculate_export_exit_status(t_shell_config *info);
int			ft_has_value_after_equal(char *arg);

void		ft_replace_env_var(char **envp, char *replace, char *var);
int			ft_get_append_length(const char *s);
void		ft_append_to_env_var(char **envp, int i, char *to_add, char *var);
void		ft_add_plus_minus(char **envp, int i, char *to_add);
void		ft_append_to_env_var_ex(char **envp, int i, char *to_add,
				char *var);

void		ft_pwd(t_shell_config *info);

void		remove_element(char **cmds, int *j);
void		unset_variable(t_shell_config *info, int index);
void		ft_unset(t_shell_config *info);

int			find_env_var_index(char **envp, char *var, int *params);
int			is_valid_unset_identifier(char *str);
int			handle_unset_errors(t_shell_config *info);
int			ft_check_export_string(char *s);
long long	ft_atoll(const char *str);
int			isnum_str(char *s);
void		add_new_env_var(t_shell_config *input, int *i, int j);
void		update_existing_env_var(t_shell_config *input, char *envp, int j);
void		print_export_with_value(t_shell_config *out_fd, char **entry,
				int key);
void		print_export_without_value(t_shell_config *out_fd, char **entry,
				int key);

//execution

void		free_commands(t_command_context *command_list);
void		free_token_list(t_token_etw *token_list);
int			ft_lstsize_commands(t_command_context *lst);
void		execution_command(t_shell_config *info);

void		free_file_discriptor(int **fd, int len);
void		close_file_descriptors(int **fd, int size);
void		wait_for_child_processes(t_shell_config *info, int lst_size);
void		exec_multiple_cmd(t_shell_config *info);

void		configure_io_redirection(t_shell_config *fd_info, int size);
void		setup_file_descriptors(t_shell_config *fd_info, int i, int size);
void		execute_child_process(t_shell_config *info, char *path,
				int fd_info, int exit_cd);
void		handle_child_process(t_shell_config *exec_params, int i, int size);

void		print_error_message(char *message1, char *message2, int c,
				t_shell_config *info);
void		print_error_message_exit(char *message, int c,
				t_shell_config *info);
void		fatal_error(char *message);
int			**create_fds(t_shell_config *info, int num_pairs, int use_pipes);

void		exec_command(char *exec_path, t_shell_config *env_vars,
				int *exit_code);
void		wait_for_child(int *exit_code, int child_pid, char *resource_path);
void		setup_fds(t_shell_config *info, int index);
int			is_builtin(t_shell_config *info);

void		run_builtin(t_shell_config *info);
void		cleanup_fds(int *fd[], int length);
void		ft_reset_io(t_shell_config *info, int ind);
void		reset_in_and_out_single(t_shell_config *info, int ind);
char		*resolve_path(t_shell_config *info, char *command_path);
char		*get_env_var(t_shell_config *env_array, char *key);

char		*check_access(t_shell_config *info, char *command_name);
char		*strip_path(char *full_path);
char		*iterate_paths(t_shell_config *info, char *arg, char ***path_dirs);
char		*find_exec_path(t_shell_config *info, char *arg, int i);
void		cleanup_resources(char *data[], int array_count, int string_count);

void		exec_single_cmd_execution(t_shell_config *vars, int pid, char *envp,
				int *exit_cd);
void		exec_single_cmd(t_shell_config *info);
void		handle_non_pipe_fds(t_shell_config *info);

//parsing

int			check_pipe_err(t_token_etw *tokens);
int			check_redir_err(t_token_etw *token);
int			check_syntax(t_shell_config *info);
void		print_error_message_extra(char *message1, char *message2, int c,
				t_shell_config *exit_code_array);

void		print_commands_part2(t_command_context *command, char *cmds);
void		print_commands(const t_token_etw *cmds, char *str_msg);

void		start_abstract(t_command_context **input);
int			add_cmd_node(t_token_etw **cmds, t_command_context **cmds_head);
int			create_args_array(t_token_etw **tokens,
				t_command_context **cmds_head, int arg_count);
int			initialize_args(t_token_etw **tokens, t_command_context **cmds);
void		print_array(char **array, char *msg);
int			generate_abstract_cmds(t_shell_config *info);

void		free_str(char *str);
int			check_valid_env_char(int str);
int			handle_exit_status(int exit_code, int *i, char **expanded_str);
int			needs_expansion(t_shell_config *envp, char **arg, int *exp_flag);

char		*extract_env_value(char **var_env_names, char *var_name);
char		*ft_strncat(char *s1, char *s2, int n);
char		*extract_env_var_name(char *env_line);
int			handle_env_variable(t_shell_config *envp, char *args, int *i,
				char **expanded_str);

void		free_2d_array(char **array);
int			env_size(char *envp[]);
char		**combine_arrays(char **array_1, char **array_2, int start,
				int *exp_flag);

void		remove_element(char **cmds, int *j);
void		print_2d_array(char **arr, char *msg);
int			expansion_success(t_shell_config *info);

int			ft_strcmp(const char *s1, const char *s2);
int			expand_variable(t_shell_config *args, char *envp, int *i,
				char **expanded_str);
char		*handle_single_quotes(char *arg, int *i, char **expanded_str);
char		*handle_double_quotes(t_shell_config *envp, char *arg, int *i,
				char **expanded_str);
char		*successful_expansion(t_shell_config *envp, char *arg,
				char **expanded_str, int *exp_flag);

int			process_heredoc_input(int fd, char *delimiter, t_shell_config *envp,
				int *exp_flag);
int			start_tokens(t_analyse *info, t_shell_config *str);
int			process_tokens(t_token_etw *ptr, t_analyse *info,
				t_shell_config *config);
int			perform_lexical_analysis(t_shell_config *config);

int			execute_heredoc(int fd, char *delimiter, t_shell_config *envp,
				int exp_flag);
int			handle_input_heredoc(t_command_context *command_args,
				t_shell_config *info, int *i);
int			handle_redirections(t_shell_config *info);

int			create_heredoc_file(void);
void		remove_elements(char **args_array, int *current_position,
				int num_elements_to_remove);
int			verify_fd_perm(char *file_path);
int			verify_fd_type(char *file_path);
int			handle_output_append(t_command_context *head_cmds, int *arg_index);

void		manage_quotes(t_analyse *pos_info);
t_token_etw	*extract_token_word(t_analyse *token_info);
void		skip_spaces(char *line, int *position);

t_token_etw	*build_token(t_tokenize_type type, char *val,
				t_token_etw	*token_next, t_token_etw *token_prev);

int			ft_is_space(int c);
t_token_etw	*get_next_token(t_analyse *info);

//start_info
int			check_alpha_flag(char *s);
int			handle_numeric_flag(char *s);
int			validate_string_content(char *s);
char		*get_old_shell_level(char *env);
char		*get_new_level_num(char *old_lvl_num, int increment);

void		update_env_with_new_level(char **env, char *new_lvl_str);
char		*calculate_next_shell_level(char *prev_shell, int increment);
void		update_shell_level(t_shell_config *env,
				char *prev_shell, char *next_shell);
void		adjust_shell_lvl(t_shell_config *env, int increment);

void		free_shell(t_shell_config *env, char *prev_shell,
				char *next_shell);

char		*bring_env(t_shell_config *info, char *res);
int			extract_value(char *s);
int			check_numeric_flag(char *s);

char		*shorten_node(char *node);
char		*clean_directory_name(char *path);
char		*construct_output(char *node_short, char *dir_name, char *user);
char		*format_prompt(char *user, char *node, char *path);
char		*format_iterm(char **environment);

void		params_start(t_token_etw *args, char *s);
void		get_args_empty(t_token_etw *args);
void		perform_child_process_and_store_output(t_token_etw *args);
void		add_missing_vars(t_shell_config *mini_env, int *index);
void		setup_env(char *orig_env[], int i, t_shell_config *mini_env,
				int count);
void		free_mini_env(char **mini_env);
void		init_env(char **env, int count, t_shell_config *mini_env);

int			count_env_vars(char **env);
char		*get_cwd(void);
char		*get_home(void);
void		start_info_ms(t_shell_config *term_name, char **mini_env);

void		printf_2d_array(char **array, char *message);
int			is_var_set(char **env, char *var);
int			find_var_index(char **env, char *var);
int			has_prefix(char *env[], char *s);
void		copy_env_var(char *orig_env[], int index, t_shell_config *mini_env);

//histpry
void		init_shell(void);

//main

void		main_loop(char *input, t_shell_config config);
int			main(int argc, char *argv[], char **envp);

//signals
void		signal_handler(int sig);
void		sigquit_handler(int signo);
void		start_signal_handlers(t_shell_config *config);
void		setup_signal_handlers(t_shell_config *config);

//terminal
void		finalize(t_shell_config *config);
void		process_input(t_shell_config *config);

void		print_error(char *s, t_shell_config *config);
void		display_tokenz(t_token_etw *info, char *msg);
int			check_parsing(t_shell_config *config);
void		handle_error(char *input);
void		start_iterm(t_shell_config *config);

void		print_tokens(const t_token_etw *cmds, char *msg);
#endif

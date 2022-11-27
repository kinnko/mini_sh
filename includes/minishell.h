/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yueyama <yuuki.java@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 15:31:36 by yueyama           #+#    #+#             */
/*   Updated: 2022/10/23 14:38:34 by ainoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define BUILTIN_CMD_COUNT 7

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define WAIT_COMMANDS 1
# define EXECUTE 2
# define HEREDOC 3

# define QUART_S 0
# define QUART_D 1

# define CD_HOME_NOT_SET "mimishell: HOME not set\n"
# define MINISHELL "minishell"
# define SYNTAX_ERROR_NEWLINE_MSG "minishell: syntax error near \
unexpected token `newline'\n"

# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>

typedef char	*t_path;
typedef char	**t_strs;
typedef int		t_fd;
typedef bool	t_true;
typedef bool	t_false;

typedef enum e_status
{
	STATUS_SUCCESS,
	STATUS_FAILS,
}				t_status;

typedef struct s_data
{
	int			state;
	int			sig_received;
	bool		run_handler;
}				t_data;

t_data			g_data;

typedef struct s_pipe
{
	t_fd		in_buf;
	t_fd		out_buf;
}				t_pipe;

typedef struct s_redirect
{
	t_fd		std_in;
	t_fd		std_out;
}				t_redirect;

typedef struct s_shell
{
	t_redirect	redirect;
	t_pipe		pipe;
	char		**builtin_list;
	char		**envp;
	char		*current_dir;
	int			exit_code;
}				t_shell;

// init.c
void			init_shell(t_shell *shell, char *envp[]);
void			set_redirect(t_redirect *redirect);
void			update_current_dir(t_shell *shell, char *new);

// cmd_*.c
int				do_cd_cmd(t_strs args, t_shell *shell);
int				do_echo_cmd(char **args);
bool			do_pwd_cmd(t_shell *shell);
bool			do_export_cmd(char **args, t_shell *shell);
bool			do_unset_cmd(char **args, t_shell *shell);
int				do_env_cmd(char **args, t_shell *shell);
int				do_exit_cmd(t_strs args, int exit_code);
bool			cd_absolute_path(char *to_path, t_shell *shell);

// envp.c
t_strs			create_new_envp(t_strs envp, char *add_env,
					ssize_t update_index);
t_strs			clone_envp(t_strs envp);
t_strs			add_envp_value(t_strs envp, char *env_key, char *add_text);
t_strs			add_envp_key(t_strs envp, char *add_text);
t_strs			overwrite_envp_value(t_strs envp, char *env_key, char *value);
size_t			get_envp_count(t_strs envp);
t_true			put_envp(t_strs envp);

// utils.c
bool			strequ(char *a, char *b);
void			free_strs(char **strs);
bool			exist_file(const char *path);
char			*path_concat(char *dir, char *file);
void			*put_error_exit(void);
int				ft_strlen_to_c(char *args, char c);
void			update_quart_in(bool *is_in_d_quart, bool *is_in_s_quart,
					char c);
char			*ft_strjoin_free(char *s1, char *s2);
bool			is_cmd(char *exec_path);
void			reset_is_in_quart(bool is_in_q[2]);

//run_builtin_cmd.c
void			run_builtin_cmd(char **args, t_shell *shell);

// execute.c
void			execute(char **args, t_shell *shell);

// expand_var.c
char			*expand_vars(char *line, int exit_code, t_strs envp);

// strs.c
void			put_strs(t_strs strs);
void			remove_strs(t_strs strs, int index);
size_t			length_strs(t_strs strs);
void			free_strs(t_strs strs);

// redirect_*.c
bool			check_redirects(t_strs args, int *exit_code);
bool			is_redirect(char *str);
bool			redirect_to(char *to_path);
bool			here_docs(char *eof, int *exit_code);
bool			redirect_from(char *from_path);
bool			redirect_add_to(char *add_to_path);

// pipe.c
bool			has_pipe(char **args);
void			recursive_execute(t_fd in, t_strs args, t_shell *shell);
bool			is_pipe(char *s);

// check_syntax.c
bool			check_syntax(char **line, t_strs *args_ptr, int *exit_code);
t_false			put_syntax_error(char *str);
bool			check_quart_syntax(char *line, int *exit_code);

// check_pipe_syntax.c
bool			check_pipe_syntax(char **line, t_strs *args_ptr);

// libft_ex.c
char			*ft_strdup_null_safe(const char *str);
char			*ft_strjoin_null_allow(const char *s1, const char *s2);
char			**split_args(char **str);

// ft_split_utils.c
size_t			get_word_count(char *line);
size_t			strclen(char *str, bool *is_in_d_quart, bool *is_in_s_quart);
void			*free_all(char **str_array, size_t count);
bool			is_redirect_pipe(char *str);

// judge_redirects.c
bool			is_redirect_add(char *str);
bool			is_redirect_to(char *str);
bool			is_redirect_from(char *str);
bool			is_start_pipe(char *str);
bool			is_here_docs(char *str);

// run_path_env_executable.c
int				run_path_env_executable(char *exec_file, char **args,
					t_strs envp);

// error_utils.c
char			*wrap_malloc(char *str);
char			**check_malloc_strs(char **strs);
t_false			export_error(char *args);

// key_value.c
bool			has_key(t_strs envp, char *key);
char			*get_key(char *env_line);
char			*get_value(char *env_line);
char			*get_value_envp(t_strs envp, char *key);

// parse_quote.c
t_strs			exclude_quote(t_strs args);
#endif /* MINISHELL_H */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnelson <lnelson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 23:34:02 by lnelson           #+#    #+#             */
/*   Updated: 2022/01/11 17:36:56 by lnelson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*######################################################*/
/*						INCLUDES						*/
/*######################################################*/

# include <signal.h>
# include "libft.h"
# include <stdio.h>
# include <errno.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>

/*######################################################*/
/*						DEFINES							*/
/*######################################################*/

# define READ_END	0
# define WRITE_END	1

# define REDIR_IN 0
# define REDIR_OUT  1
# define REDIR_IN2 2
# define REDIR_OUT2  3

# define CMD 1
# define ARG 2
# define FILE 3
# define REDIR 4
# define PIPE 5
# define QUOTED 6
# define NOSPEC 7

# define ERROR_MALLOC "minishell: malloc issued, exiting minishell.\n"
# define WRONGF_PIPE "minishell: pipe placed in first word.\n"
# define WRONGL_PIPE "minishell: pipe placed in last word.\n"
# define MULTI_PIPE "minishell: sequence of multiple pipes.\n"
# define WRONG_REDIR "minishell: redirection without a file.\n"
# define MULTI_REDIR "minishell: \"<<\", \">>\", \"<\", \">\" only.\n"
# define OPEN_QUOTE "minishell: quote non closed.\n"
# define MAX_ARG "\033[0;31mMinishell$ \033[0;37m exit: too many arguments\n"
# define BUILTIN_ECHO "echo"
# define BUILTIN_CD "cd"
# define BUILTIN_PWD "pwd"
# define BUILTIN_EXPORT "export"
# define BUILTIN_UNSET "unset"
# define BUILTIN_ENV "env"
# define BUILTIN_EXIT "exit"

/*######################################################*/
/*						STRUCTURES						*/
/*######################################################*/

typedef struct s_token
{
	int				id;
	char			type;
	char			*str;
	struct s_token	*next;
}				t_tokenl;

typedef struct env_str
{
	char	*name;
	char	*value;
	int		env_display;
}				t_env_str;

typedef struct s_redir
{
	int				type;
	char			*filename;
	struct s_redir	*next;
}				t_redir;

typedef struct s_command
{
	char				**args;
	t_redir				*redir;
	int					fd[2];
	struct s_command	*next;
}				t_cmd;

typedef struct s_data
{
	t_list	*cmd_list;
	t_list	**env_list;
	char	**envp;
	int		fork_nbr;
	pid_t	*pids;
	int		index;
}				t_data;

extern int	g_exit_status;

/*######################################################*/
/*						SOURCES							*/
/*######################################################*/

/*			MAIN_N.C 				*/

void			ft_free_content(void *content);
t_list			*transform(t_cmd **first, t_list **lst_env);
void			initialise(int ac, char **av, char **env, t_list **l_env);
t_list			*get_commands(char *line, t_list **lst_env);
void			exit_main(t_list **lst_env, t_list **cmds);
void			routine(char *line, t_data *data, t_list **lst_env,
					t_list **cmds);
int				line_contain_chars(char *line);

/*			MAIN_UTILS				*/

void			init_data(t_data *data, t_list **lst_env);
int				check_tokens_syntax_routine(char *line, t_list **lst_env);
void			exit_routine(char **str, t_list **cmds);
t_list			*transform(t_cmd **first, t_list **lst_env);
void			print_tokens(t_tokenl *list);
void			print_redir_lst(t_redir *first);
void			print_cmd_lst(t_cmd *list);
void			print_content(void *content);
void			exec_print(void *content);

/*			PRINT_DATA.C			*/

void			print_tokens(t_tokenl *list);
void			print_redir_lst(t_redir *first);
void			print_cmd_lst(t_cmd *list);
void			print_content(void *content);
void			exec_print(void *content);
/*
**	BUILTINS
*/

/*			FT_CD.C 				*/

int				change_path(char *path, t_list *lst_env);
int				change_home(t_list *lst_env, char **path);
void			builtin_cd(char **args, t_list *lst_env);

/*			FT_ECHO.C 				*/

int				get_len(char **strs);
void			builtin_echo(char **av); // cmd->args (easy)

/*			FT_ENV.C 				*/

void			print_env(void *content);
void			builtin_env(t_list *lst_env); // env (easy)

/*			FT_EXIT.C 				*/

int				check_numerical(const char *str, int *i);
int				increment_nbr(long long *nbr, const char *str,
					int *i, int sign);
void			ft_exit(t_data *data, int pid);
unsigned char	atoi_exit(const char *str);
void			builtin_exit(char **args, t_data *data, int pid);

/*			EXPORT_UTILS.C 			*/

void			print_export(void *content);
int				check_export_validity(char *str);
int				compare_data(t_list *a, t_list *b);
void			lst_swap(t_list *a, t_list *b);
void			ft_sort_export(t_list *lst);

/*			FT_EXPORT.C 			*/

void			modify_var(t_list *list, char *name, char *value);
void			add_name_and_value(t_list *list, char *name, char *value,
					int export_env);
void			export_to_list(char *str, t_list *env_lst, int export_env);
int				export_strs(char **strs, t_list *env_lst);
void			builtin_export(t_list *env_lst, char **strs);

/*			FT_PWD.C 				*/

void			builtin_pwd(void);

/*
**	LISTS
*/

/*			FT_TOK_LST.C			*/

void			ft_lst_clear(t_tokenl *first);
t_tokenl		*ft_toknew(void);
t_tokenl		*ft_tokadd_back(t_tokenl **begin_list, t_tokenl *new);
void			ft_tok_free(t_tokenl *token);
void			ft_tokall_free(t_tokenl **first);

/*			FT_TOK_LST_UTILS.C		*/

void			ft_tok_insert(t_tokenl *this, t_tokenl *inserted);

/*			FT_CMD_LST_UTILS.C 		*/

int				get_arg_nbr(t_tokenl *token);
t_cmd			*ft_cmdget_last(t_cmd *first);
void			ft_cmd_free(void *data);
void			ft_cmdall_free(t_cmd **first);

/*			FT_CMD_LST.C 			*/

void			ft_cmdadd_back(t_cmd **begin_list, t_cmd *new);
char			*null_string_array(char **arr);
char			**load_args(t_tokenl *token);
int				is_cmd_in_pipe(t_tokenl *token);
t_cmd			*ft_cmdnew(t_cmd **fst, t_tokenl *token, t_redir *red,
					t_list **env);

/*			FT_REDIR_LST.C 			*/

int				xft_strcmp(char *s1, char *s2);
void			ft_rediradd_back(t_redir **begin_list, t_redir *new);
t_redir			*ft_redirnew(t_tokenl *token, t_cmd **first, t_list **lst_env);
void			ft_redir_free(t_redir *redir);
void			ft_redirall_free(t_redir **first);

/*
**	REST
*/

/*			ACCES.C				*/
int				check_acces_path(char *str, t_list *env, char **path);

/*			GET_PATH.C 			*/

char			**get_paths(t_list *env);
void			free_paths(char **path);

/*			 EXEC.C				*/

void			exit_invalid_path(char *str, t_data *data);
int				try_acces(char *cmd_name, t_list *env, char **cmd_path);
void			run_cmd(t_cmd *cmd, t_cmd *prev, t_cmd *next, t_data *data);
void			exec_cmd(t_cmd *cmd, t_cmd *prev,
					t_cmd *next_cmd, t_data *data);
void			exec_cmds(t_list *lst, t_data *data);

/*			PIPEFLOW.C				*/
void			pipeflow(t_cmd *next, t_cmd *prev, t_cmd *cmd);

/*			REDIRECTIONS			*/

int				redirect(t_cmd *cmd, int pid, t_data *data);
int				redir_out(t_redir *redir, int *fd_out, int pid, t_data *data);
int				redir_in(t_redir *redir, int *fd_in, int pid,
					t_data *data);
int				redir_append(t_redir *redir, int *fd_out, int pid,
					t_data *data);
int				redir_heredoc(t_redir *redir, int *fd_in);

/*			EXEC_BUILTINS			*/

int				check_builtin(char *s1, char *s2);
int				is_builtin(char *str);
int				run_builtin(char **args, t_list **env, t_data *data, int pid);
int				exec_builtin(t_cmd *cmd, t_list **env, t_data *data);

/*			FT_CONVERT.C 		*/

char			*cat_elems(char *name, char *value);
char			**ft_convert(t_list *head);

/*			FT_COPY_ENV.C 		*/

char			*get_name(char *str, char *name);
char			*get_value_str(char *str, char *value);
void			ft_lst_copyenv(char **env, t_list **head);

/*			FT_SEARCH_VALUE.C	*/

int				found_in_env(char *str, void *content);
char			*ft_get_value(void *content);
char			*ft_search_value(t_list *lst, char *name);
int				ft_check_if_exists(t_list *lst, char *name);

/*			FT_SORT_EXPORT.C 	*/

int				compare_data(t_list *a, t_list *b);
void			lst_swap(t_list *a, t_list *b);
void			ft_sort_export(t_list *lst);

/*			FT_UNSET.C 			*/

void			ft_delete_relink(t_list **list, t_list *prev, t_list *cur);
void			remove_from_list(char *str, t_list **list);
void			builtin_unset(t_list **lst, char **strs);

/*			PARSING_UTILS.C		*/

void			exit_parser(char *str, t_tokenl **first, t_list **lst_env);
int				verif_line(char *str);
void			skip_char(char *str, char a, int *i);
char			*ft_strjoin_free_helper(char *s1, char *s2, char **s3, int i);
char			*ft_strjoin_free_s1(char *s1, char *s2);

/*			PARCE_TOKENS.C		*/

int				join_char_to_tok(t_tokenl *token, char a);
int				quotes_add(t_tokenl *last, int *i, char *str);
int				token_add(t_tokenl **first, int *i, char *str);
int				add_pipe(t_tokenl **first, int *i, char *str);
t_tokenl		*parce_cmd_line(char *str, t_list **lst_env);

/*			EXPAND_DOLLAR_UTILS.C	*/

int				dollar_add_env_var(t_tokenl *last);
int				dollar_is_digit(t_tokenl *last, int *i,
					char *str, t_list **env);
int				dollar_addqts_helper(t_tokenl *last, int *i,
					t_list **env, char *str);
int				dollar_addqts(t_tokenl *last, int *i, t_list **env, char *str);

/*			EXPAND_DOLLAR.C			*/

int				dollar_add_env_var(t_tokenl *last);
int				dollar_split_helper(t_tokenl **temp, t_tokenl *from,
					char *str, int *i);
int				dollar_add_split(t_tokenl **last, char *str, char **d);	
int				dollar_add_helper(t_tokenl **last, t_list **env, char **d);
int				dollar_add(t_tokenl **last, int *i, t_list **env, char *str);

/*			EXPAND_QUOTES.C			*/

int				expand_dquotes(t_tokenl *last, int *i, char *str, t_list **env);
int				expand_squotes(t_tokenl *last, int *i, char *str);
int				expand_quotes(t_tokenl *last, int *i, t_list **env, char *str);

/*			EXPAND_WORDS.C			*/

void			exit_expander(t_tokenl **first, t_list **lst_env);
int				expand_word_starter(t_tokenl **last, char **str, int *i);
int				expand_word_finisher(char *str);
int				expand_word(t_tokenl **last, t_list **env, int i);
void			expand_words(t_tokenl **first, t_list **env);

/*			GET_LISTS.C 			*/

int				coutn_cmds(t_tokenl *first);
t_cmd			*get_cmd_lst(t_tokenl *first, t_list **lst_env);
void			exit_get_lst(t_cmd **fst, t_tokenl *token, t_list **env);

/*			PARSE_REDIRS_UTILS.C	*/

int				add_dquotes_helper(int *i, char *str, t_tokenl *last,
					t_list **env);
int				add_dquotes(int *i, char *str, t_tokenl *last, t_list **env);

/*			PARSE_REDIRS.C 			*/

int				add_squotes(int *i, char *str, t_tokenl *last);
int				add_quotes(int *i, char *str, t_tokenl *last, t_list **env);
int				addred_helper1(int *i, char *str, t_tokenl *last);
int				addred_helper2(int *i, char *str, t_tokenl *last, t_list **env);
int				add_redirs(t_tokenl **first, int *i, char *str, t_list **env);

/*			PARSE_REDIRS_DOLLAR.C	*/

int				dollar_fwd_by_digit(int *i, char *str, t_tokenl *last,
					t_list **env);
int				dollar_add_exitsig(int *i, t_tokenl *last);
int				add_dollar_inquote(int *i, char *str, t_tokenl *last,
					t_list **env);
int				add_dollar_helper(int *i, char *str, t_tokenl *last);
int				add_dollar(int *i, char *str, t_tokenl *last, t_list **env);

/*			SPEC_TOKENS_UTILS		*/

int				spec_first_token_type(t_tokenl *first, int *key);
int				spec_last_token_type(t_tokenl *last, int key);
int				spec_last_first_token(t_tokenl *token, int *key);

/*			SPEC_TOKENS.C			*/

int				spec_redir(t_tokenl *token);
void			spec_cmd(t_tokenl *token, int *key);
void			spec_pipe(t_tokenl *token, int *key);
int				spec_types(t_tokenl *first);

/*			CHECK_SYNTAX.C			*/

int				dollar_fwd_by_digit(int *i, char *str, t_tokenl *last,
					t_list **env);
int				check_pipe_syntax(t_tokenl *token);
int				check_redir_syntax(t_tokenl *token);
int				check_syntax_error(t_tokenl *token);

/*			SIGNAL.C				*/

void			signal_in_main(void);
void			signal_in_child(void);
void			signal_heredoc(void);

/*			HANDLERS.C				*/

void			main_handle_sigint(int sig);
void			handle_heredoc(int sig);
void			handle_child(int sig);

/*			UTILS.C					*/

char			*ft_strjoin_char(char *str, char a);
int				ft_strcmp(char *s1, char *s2);
int				ft_strlen_p(char *str);
char			*ft_strdup_to(char *str, char a);
int				get_fork_nbr(t_list *lst);

/*			UTILS_2.C				*/

int				ft_max(int n, int n2);
int				is_only_whitespace(char *str);
void			exit_str(int i, char *str);
int				line_contain_chars(char *line);

/*			FREE UTILS				*/

void			ft_free_cmds(void *content);
void			ft_free_content(void *content);
void			ft_free_strs(char **strs);

#endif

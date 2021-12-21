/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdruez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 12:42:49 by bdruez            #+#    #+#             */
/*   Updated: 2021/12/14 17:54:31 by aedouard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
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

/*
** ----- Defines ---------------------------------------------------------------
*/

#define READ_END	0
#define WRITE_END	1

#define NOPIPE		0
#define FIRST_PIPE	1
#define MID_PIPE	2
#define LAST_PIPE	3
#define	PIPE		4
#define REDIR_IN 0
#define REDIR_OUT  1
#define REDIR_IN2 2
#define REDIR_OUT2  3

/*
** ----- Enums -----------------------------------------------------------------
*/

/*
** ----- Structures ------------------------------------------------------------
*/

typedef struct env_str
{
	char *name;
	char *value;
	int export;
}	t_env_str;

/*typedef struct command
{
	char **args;
	int pipe_type;
	
}	t_cmd;*/

typedef struct redir
{
    int 			type; // > ou >> ou <
    char 			*filename;
    struct redir	*next;
}	t_redir;

typedef struct command
{
    char				**args;
    int                type; //PIPE ou NORMAL
    int                fd[2];
    struct redir    *redir; //NULL si non redir
}	t_cmd;


/*
** ----- Functions prototypes --------------------------------------------------
*/

void	builtin_echo(char **av);
void	builtin_pwd();
void	builtin_unset(t_list *lst, char **strs);
void    builtin_exit(char **args, t_list *lst_env, t_list *lst_export);
void	builtin_cd(char **args, t_list *lst_env, t_list *lst_export);
void	builtin_env(t_list *lst_env);
void	builtin_export(t_list *export_lst, t_list *env_lst, char **strs);
//t_env	*create_node(char *str);
//t_env	*add_node(t_env *list, int pos, char *str);
//void	ft_copy_env(char **env, t_env **head);
//int	ft_env(t_env **env);
//t_env	*destroy_node(t_env *head, int pos);
//t_env	*destroy_chain(t_env *head, int chain_size);
//int	ft_unset(t_env **head, char *str);
//int	ft_envsize(t_env *lst);
//char **ft_convert (t_env *head);
//char *find_str_env(t_env *lst, char *str);
void	ft_lst_copyenv(char **env, t_list **head);
void	ft_free_content(void *content);
char	*ft_search_value(t_list *lst, char *name);
int	found_in_env(char *str, void *content);
char **ft_convert(t_list *head);
int	ft_check_if_exists(t_list *lst, char *name);
char	*get_name(char *str, char *name);
char *get_value_str(char *str, char *value);
void	ft_free_content(void *content);
void    ft_sort_export(t_list *lst);
void	export_to_list(char *str, t_list *export_lst, t_list *env_lst, int export_env);
void    ft_exit(t_list *lst_env, t_list *lst_export);



void    exec_tests(t_list **head, char **envp);
int     exec_cmds(t_list *lst, char **envp);


// -------------------------------------------------------------------------- //
// -------------------------------------------------------------------------- //

#endif

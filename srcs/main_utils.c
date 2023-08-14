/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnelson <lnelson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 23:58:03 by lnelson           #+#    #+#             */
/*   Updated: 2022/01/11 19:21:03 by lnelson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_data(t_data *data, t_list **lst_env)
{
	data->pids = NULL;
	data->env_list = lst_env;
	data->index = 0;
	data->envp = NULL;
}

int	check_tokens_syntax_routine(char *line, t_list **lst_env)
{
	t_tokenl	*tokens;

	tokens = parce_cmd_line(line, lst_env);
	if (tokens == NULL)
		exit_str(1, ERROR_MALLOC);
	spec_types(tokens);
	expand_words(&tokens, lst_env);
	if (check_syntax_error(tokens) == 1)
	{
		ft_tokall_free(&tokens);
		return (1);
	}
	else
		ft_tokall_free(&tokens);
	return (0);
}

void	exit_routine(char **envp, t_list **cmds)
{
	if (envp == NULL)
		ft_lstclear(cmds, *(ft_cmd_free));
	else
	{
		ft_lstclear(cmds, *(ft_cmd_free));
		ft_free_strs(envp);
	}
	exit_str(1, ERROR_MALLOC);
}

t_list	*transform(t_cmd **first, t_list **lst_env)
{
	t_cmd	*temp;
	t_list	*ret;
	t_list	*x;

	x = NULL;
	ret = NULL;
	temp = *first;
	while (temp)
	{
		x = ft_lstnew((void *)temp);
		if (x == NULL)
		{
			ft_cmdall_free(first);
			ft_lstclear(lst_env, *ft_free_content);
			ft_putstr_fd(ERROR_MALLOC, 2);
			exit(127);
		}
		ft_lstadd_back(&ret, x);
		temp = temp->next;
	}
	return (ret);
}

/*
void	print_tokens(t_tokenl *list)
{
	t_tokenl	*temp;

	temp = list;
	write(0, "\n", 1);
	while (temp != NULL)
	{
		printf("token id: %i type : %s  \tstr = %s\n", 
		temp->id, 
		(temp->type == 1 ? "CMD" :
		(temp->type == 2 ? "ARG" :
		(temp->type == 3 ? "FILE" :
		(temp->type == 4 ? "REDIR" :
		(temp->type == 5 ? "PIPE" :
		(temp->type == 6 ? "QUOTED" :
						   "NOSPEC")))))), 
		temp->str);
		temp = temp->next;
	}
	write(0, "\n", 1);
}

void	print_redir_lst(t_redir *first)
{
	while (first)
	{
		printf("type: %s \tfilename: %s\n", 
		first->type == REDIR_OUT ? ">" :
		first->type == REDIR_IN ? "<" :
		first->type == REDIR_OUT2 ? ">>" : "<<", 
		first->filename);
		first = first->next;
	}
	return ;
}

void	print_cmd_lst(t_cmd *list)
{
	int i;
	int	j;

	i = 1;
	j = 0;
	if (list == NULL)
		return ;
	printf("\n\t\tCOMMANDS LIST:\n");
	while(list)
	{
		printf("\t\tcmd_lst %i | \t fd[0] = %i fd[1] = %i\n",
		i,
		list->fd[0], 
		list->fd[1]);
		j = 0;
		if (list->args == NULL)
			printf("NULL\n");
		else
		{
			while (list->args[j])
			{
				if (j == 0)
					printf("-cmd: %s\n", list->args[j]);
				else
					printf("--arg: %s\n", list->args[j]);
				j++;
			}
		}
		i++;
		write(1, "\nRedirs:_____\n", 15);
		if (list->redir == NULL)
			printf("NULL\n");
		else
			print_redir_lst(list->redir);
		write(1, "\n\n\n", 3);
		list = list->next;
	}
	return ;
}

void	print_content(void *content)
{
	t_env_str	*content2;

	content2 = (t_env_str *)content;
	printf("variable : %s\n", content2->name);
	printf("contenu : %s\n", content2->value);
}

void	exec_print(void *content)
{
	t_cmd	*cmd;

	cmd  = (t_cmd *)content;
	printf("%s    ", cmd->args[0]);
	printf("%s\n", cmd->args[1]);
	//printf("%d\n", cmd->type);
}
*/

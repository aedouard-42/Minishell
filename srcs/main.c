/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnelson <lnelson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 12:40:30 by bdruez            #+#    #+#             */
/*   Updated: 2022/01/11 18:36:59 by lnelson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status;

void	exit_main(t_list **lst_env, t_list **cmds)
{
	if (*cmds != NULL)
		ft_lstclear(cmds, *(ft_cmd_free));
	ft_lstclear(lst_env, *(ft_free_content));
	rl_clear_history();
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	exit (g_exit_status);
}

void	initialise(int ac, char **av, char **env, t_list **l_env)
{
	(void)ac;
	(void)av;
	*l_env = NULL;
	g_exit_status = 0;
	signal_in_main();
	ft_lst_copyenv(env, l_env);
	if (*l_env == NULL)
		exit (1);
	return ;
}

t_list	*get_commands(char *line, t_list **lst_env)
{
	t_tokenl	*tokens;
	t_cmd		*cmds;
	t_list		*ret;

	ret = NULL;
	tokens = parce_cmd_line(line, lst_env);
	if (tokens == NULL)
		return (NULL);
	spec_types(tokens);
	expand_words(&tokens, lst_env);
	cmds = get_cmd_lst(tokens, lst_env);
	ft_tokall_free(&tokens);
	if (cmds != NULL)
		ret = transform(&cmds, lst_env);
	else
	{
		ft_tokall_free(&tokens);
		exit_str(1, ERROR_MALLOC);
	}
	return (ret);
}

void	routine(char *line, t_data *data, t_list **lst_env, t_list **cmds)
{
	init_data(data, lst_env);
	*cmds = get_commands(line, lst_env);
	if (check_tokens_syntax_routine(line, lst_env) == 1)
	{
		if (*cmds == NULL)
			exit_str(1, ERROR_MALLOC);
		data->cmd_list = *cmds;
		data->fork_nbr = get_fork_nbr(*cmds);
		data->envp = ft_convert(*lst_env);
		if (data->envp == NULL)
			exit_routine(data->envp, cmds);
		if (data->fork_nbr != 0)
			data->pids = malloc(sizeof(int) * data->fork_nbr);
		if (data->pids == NULL && data->fork_nbr != 0)
			exit_routine(data->envp, cmds);
		exec_cmds(*cmds, data);
	}
	signal_in_main();
	if (data->envp != NULL)
		ft_free_strs(data->envp);
	if (data->pids != NULL)
		free(data->pids);
}

int	main(int ac, char **av, char **env)
{
	char		*line;
	t_list		*commands;
	t_list		*lst_env;
	t_data		data;

	commands = NULL;
	initialise(ac, av, env, &lst_env);
	while (1)
	{
		line = readline("\033[0;31mminishell$ \033[0;37m");
		if (line == NULL)
			exit_main(&lst_env, &commands);
		if (line_contain_chars(line) == 1)
			add_history(line);
		if (verif_line(line) == 1)
		{
			if (commands != NULL && commands != (void *)-1)
				ft_lstclear(&commands, *(ft_cmd_free));
			routine(line, &data, &lst_env, &commands);
		}
	}
	return (0);
}

/*TODO LIST

- comment excve and check if supressed leaks still exist
- have a look on heredoc re-calling open after write -> USE STR instead of tmp FD
- look at all mallocs and protect them
- norme
- simulate a correction

salut))
*/

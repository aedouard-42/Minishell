/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdruez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 12:40:30 by bdruez            #+#    #+#             */
/*   Updated: 2021/12/14 17:46:46 by aedouard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	print_content(void *content)
{	
	t_env_str *content2 = (t_env_str *)content;
	printf("variable : %s\n", content2->name);
	printf("contenu : %s\n", content2->value);
}


void	ft_free_content(void *content)
{
	t_env_str *content2 = (t_env_str *)content;
	free(content2->name);
	free(content2->value);
	content2->name = NULL;
	content2->value = NULL;

	free(content2);
}

void	ft_free_cmds(void *content)
{
	t_cmd *content2 = (t_cmd *)content;

	int i = 0;

	while(content2->args[i])
	{
		free(content2->args[i]);
		i++;
	}
	free(content2->args);

	free(content2);
}



/*void print_env(char **env)
{
	int i;
		
	i = 0;
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
}*/

void	exec_print(void *content)
{
	t_cmd *cmd = (t_cmd *)content;

	printf("%s    ", cmd->args[0]);
	printf("%s\n", cmd->args[1]);

	//printf("%d\n", cmd->type);

}

int	main(int ac, char **av, char **env)
{
	t_list *lst_env;
	t_list *lst_export;

	(void)ac;
	(void)av;

	lst_env = NULL;
	lst_export = NULL;

	ft_lst_copyenv(env, &lst_env);
	char *result = ft_search_value(lst_env, "HOME");
	printf("%s\n", result);
	//ft_lst_copyenv(env, &lst_export);


	char *str;
	str = NULL;
	char **args;
	t_list *exec_head;

	exec_head = NULL;


	exec_tests(&exec_head, env);

	ft_lstiter(exec_head, &exec_print);

	exec_cmds(exec_head, env);


	/*while (1)
	{
		str = readline("minishell ");
		//printf("%s\n", str);
		args = ft_split(str, ' ');
		if (ft_strncmp(args[0], "echo", 4) == 0)
			builtin_echo(args);
		if (ft_strncmp(args[0], "env", 3) == 0)
			builtin_env(lst_env);
		if (ft_strncmp(args[0], "unset", 5) == 0)
			builtin_unset(lst_env, args);
		if (ft_strncmp(args[0], "export", 6) == 0)
			builtin_export(lst_export, lst_env,  args);// export no arg exports "export into export list"
		if (ft_strncmp(args[0], "exit", 5) == 0)
			builtin_exit(args, lst_env, lst_export);
		if (ft_strncmp(args[0], "cd", 2) == 0)
			builtin_cd(args, lst_env, lst_export);
		if (ft_strncmp(args[0], "pwd", 3) == 0)
			builtin_pwd();
		if (ft_strncmp(args[0], "$?", 2) == 0)
			printf("%d\n", errno);
	}*/

	//ft_unset(lsthead, av);
	//ft_lstiter(lsthead, ft_env);
	//envcpy = ft_convert(lsthead);
	//print_env(envcpy);
	//ft_export(export_head, lsthead,  av+1);

	//ft_unset(lsthead, av);


	//ft_cd(av, lst_env, lst_export);

	ft_lstclear(&exec_head, &ft_free_cmds);

	return (0);
}

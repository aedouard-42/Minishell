/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnelson <lnelson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 15:47:56 by lnelson           #+#    #+#             */
/*   Updated: 2022/01/11 21:12:31 by lnelson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*  maybe add something about errno
	if (g_exit_status == 0)
	g_exit_status = errno;
*/
void	ft_exit(t_data *data, int pid)
{
	ft_lstclear(data->env_list, &ft_free_content);
	ft_lstclear(&(data->cmd_list), &ft_cmd_free);
	free(data->pids);
	data->pids = NULL;
	ft_free_strs(data->envp);
	rl_clear_history();
	free(data->pids);
	if (pid != 0)
		printf ("exit\n");
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	exit(g_exit_status);
}

int	increment_nbr(long long *nbr, const char *str, int *i, int sign)
{
	while (ft_isdigit(str[*i]) && (str[*i]))
	{
		*nbr = *nbr * 10 + str[*i] - '0';
		*i += 1;
		if (*nbr >= 922337203685477580 && str[*i] != '\0')
		{
			if (str[*i] > '8')
				return (2);
			else if (str[*i] == '8' && sign == 1)
				return (2);
		}
	}
	return (0);
}

int	check_numerical(const char *str, int *i)
{
	while (ft_is_space(str[*i]) && str[*i])
		*i += 1;
	if (str[*i])
	{
		ft_putstr_fd("\033[0;31mMinishell$ \033[0;37mexit : ", 2);
		ft_putstr_fd((char *)str, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		return (2);
	}
	return (0);
}

unsigned char	atoi_exit(const char *str)
{
	int				sign;
	int				i;
	long long		nbr;
	unsigned int	ret;

	i = 0;
	nbr = 0;
	sign = 1;
	while (ft_is_space(str[i]) && str[i])
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -sign;
		i++;
	}
	ret = increment_nbr(&nbr, str, &i, sign);
	if (ret != 2)
		ret = check_numerical(str, &i);
	if (ret == 2)
		return (ret);
	ret = (unsigned char)(nbr * sign);
	return (ret);
}

void	builtin_exit(char **args, t_data *data, int pid)
{
	if (!args || !args[1])
		ft_exit(data, pid);
	else if (args && args[1] && args[2])
	{
		ft_putstr_fd(MAX_ARG, 2);
		g_exit_status = 1;
	}
	else if (args[1])
	{
		if (is_only_whitespace(args[1]))
			ft_exit(data, pid);
		else
		{
			g_exit_status = atoi_exit(args[1]);
			ft_exit(data, pid);
		}
	}
}

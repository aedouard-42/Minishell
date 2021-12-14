/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aedouard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 16:26:40 by aedouard          #+#    #+#             */
/*   Updated: 2021/11/08 16:27:00 by aedouard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_env(void *content)
{
	t_env_str *content2 = (t_env_str *)content;
	if (content2->name !=NULL && content2->value !=NULL)
		printf("%s=%s\n", content2->name, content2->value);
}

void	builtin_env(t_list *lst_env)
{
	ft_lstiter(lst_env, print_env);
	errno = 0;
}

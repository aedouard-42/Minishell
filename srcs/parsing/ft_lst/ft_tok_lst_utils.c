/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tok_lst_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnelson <lnelson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 13:12:22 by lnelson           #+#    #+#             */
/*   Updated: 2022/01/09 23:00:23 by lnelson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_tok_insert(t_tokenl *this, t_tokenl *inserted)
{
	t_tokenl	*next;

	next = this->next;
	this->next = inserted;
	inserted->next = next;
	return ;
}

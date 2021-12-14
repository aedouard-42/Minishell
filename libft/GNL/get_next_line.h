/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aedouard <aedouard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 16:48:47 by aedouard          #+#    #+#             */
/*   Updated: 2021/06/18 15:34:04 by aedouard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include "../libft.h"

size_t	gnl_strlen(const char *s);
void	*gnl_memmove(void *dst, const void *src, size_t len);
char	*gnl_join_str(char const *s1, char const *s2);
int		gnl_has_return(char *str);

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 20
# endif

#endif

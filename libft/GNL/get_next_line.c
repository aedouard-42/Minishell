/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aedouard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 14:28:23 by aedouard          #+#    #+#             */
/*   Updated: 2021/06/11 15:02:36 by aedouard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*get_save(char *save)
{
	char	*rtn;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!save)
		return (NULL);
	while (save[i] && save[i] != '\n')
		i++;
	if (!save[i])
	{
		free(save);
		return (NULL);
	}
	rtn = malloc(sizeof(char) * ((gnl_strlen(save) - i) + 1));
	if (!rtn)
		return (NULL);
	i++;
	while (save[i])
		rtn[j++] = save[i++];
	rtn[j] = '\0';
	free(save);
	return (rtn);
}

static char	*get_line(char *str)
{
	int		i;
	char	*rtn;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	rtn = malloc(sizeof(char) * (i + 1));
	if (!rtn)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		rtn[i] = str[i];
		i++;
	}
	rtn[i] = '\0';
	return (rtn);
}

static void	update_save_line(char **buff, char ***line, char **save)
{
	free(*buff);
	**line = get_line(*save);
	*save = get_save(*save);
}

int	get_next_line(int fd, char **line)
{
	char			*buff;
	static char		*save;
	int				reader;

	reader = 1;
	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (-1);
	while (!gnl_has_return(save) && reader != 0)
	{
		reader = read(fd, buff, BUFFER_SIZE);
		if (reader == -1)
		{
			free(buff);
			return (-1);
		}
		buff[reader] = '\0';
		save = gnl_join_str(save, buff);
	}
	update_save_line(&buff, &line, &save);
	if (reader == 0)
		return (0);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 18:03:08 by qdang             #+#    #+#             */
/*   Updated: 2019/10/21 16:16:20 by qdang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft/libft.h"

int		put_next_line(const int fd, char **save, char **line)
{
	char	*temp;
	int		i;

	i = 0;
	while (save[fd][i] && save[fd][i] != '\n')
		i++;
	*line = ft_strsub(save[fd], 0, i);
	if (save[fd][i] == 0)
		save[fd] = NULL;
	else
	{
		temp = ft_strsub(save[fd], i + 1, ft_strlen(save[fd]) - i - 1);
		free(save[fd]);
		save[fd] = ft_strdup(temp);
		free(temp);
	}
	return (1);
}

int		get_next_line(const int fd, char **line)
{
	static char	*save[FD_SIZE];
	char		buff[BUFF_SIZE + 1];
	char		*temp;
	int			amber;

	if (fd < 0 || line == NULL || read(fd, buff, 0) < 0)
		return (-1);
	while ((amber = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[amber] = '\0';
		if (save[fd] == NULL)
			save[fd] = ft_strnew(0);
		temp = ft_strdup(save[fd]);
		free(save[fd]);
		save[fd] = ft_strjoin(temp, buff);
		free(temp);
		if (ft_strchr(buff, '\n'))
			break ;
	}
	if (amber == 0 && (save[fd] == NULL || !save[fd][0]))
		return (0);
	return (put_next_line(fd, save, line));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yironmak <yironmak@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 13:08:51 by yironmak          #+#    #+#             */
/*   Updated: 2021/10/15 17:08:09 by yironmak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	get_bytes_read(char *buf, int fd)
{
	if (ft_strlen(buf))
		return (ft_strlen(buf));
	else
		return (read(fd, buf, BUFFER_SIZE));
}

char	*check_buf(char *buf, char **line)
{
	if (ft_strlen(*line) != 0)
	{
		buf[0] = '\0';
		return (*line);
	}
	*line = ft_strjoin(*line, buf);
	buf[0] = '\0';
	return (*line);
}

char	*t_get_next_line(char *buf, char *line, int fd)
{
	int			bytes_read;
	char		*p_n;

	bytes_read = get_bytes_read(buf, fd);
	if (bytes_read <= 0)
	{
		free(line);
		return (NULL);
	}
	while (bytes_read)
	{
		buf[bytes_read] = '\0';
		p_n = ft_strchr(buf, '\n');
		if (p_n)
		{
			*p_n = '\0';
			line = ft_strjoin(line, buf);
			line = ft_strjoin(line, "\n");
			ft_strlcpy(buf, p_n + 1, BUFFER_SIZE);
			return (line);
		}
		line = ft_strjoin(line, buf);
		bytes_read = read(fd, buf, BUFFER_SIZE);
	}
	return (check_buf(buf, &line));
}

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE + 1];
	char		*line;

	if (fd < 0)
		return (NULL);
	line = malloc(1);
	line[0] = '\0';
	return (t_get_next_line(buf, line, fd));
}

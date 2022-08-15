/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssawane <ssawane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 13:50:03 by ssawane           #+#    #+#             */
/*   Updated: 2022/08/10 13:54:56 by ssawane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static char	*ft_read(int fd)
{
	char	buffer[10000];
	char	*str;
	ssize_t	bytes;

	bytes = read(fd, buffer, 10000);
	if (bytes <= 0)
		return (NULL);
	buffer[bytes] = '\0';
	str = ft_strdup(buffer);
	return (str);
}

static char	*disconnect(char **s_res)
{
	char	*str;
	char	*point;
	char	*tmp;

	if (ft_strlen(*s_res) == 0)
	{
		free(*s_res);
		*s_res = NULL;
		return (NULL);
	}
	point = ft_strchr(*s_res, '\n');
	if (point == 0)
	{
		str = ft_strdup(*s_res);
		free(*s_res);
		*s_res = NULL;
		return (str);
	}
	*point = '\0';
	str = ft_strjoin(*s_res, "\n");
	point++;
	tmp = *s_res;
	*s_res = ft_strdup(point);
	free(tmp);
	return (str);
}

static void	connect(char **s_res, int fd)
{
	char	*tmp;
	char	*str;

	while (ft_strchr(*s_res, '\n') == 0)
	{
		str = ft_read(fd);
		tmp = *s_res;
		if (str == 0)
			break ;
		else
			*s_res = ft_strjoin(*s_res, str);
		free(tmp);
		free(str);
	}
}

char	*get_next_line(int fd)
{
	static char	*s_res;
	char		*res;

	if (fd < 0)
		return (NULL);
	if (s_res == 0)
	{
		s_res = ft_read(fd);
		if (s_res == 0)
			return (NULL);
	}
	connect(&s_res, fd);
	res = disconnect(&s_res);
	return (res);
}

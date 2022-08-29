/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_checks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssawane <ssawane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 10:29:12 by ssawane           #+#    #+#             */
/*   Updated: 2022/08/28 10:35:52 by ssawane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	ismap(char *line)
{
	if (!isempty(line))
	{
		if (!ft_strncmp(line, "NO ", 3)
			|| !ft_strncmp(line, "SO ", 3)
			|| !ft_strncmp(line, "WE ", 3)
			|| !ft_strncmp(line, "EA ", 3)
			|| !ft_strncmp(line, "F ", 2)
			|| !ft_strncmp(line, "C ", 2))
			return (0);
		else
			return (1);
	}
	return (0);
}

int	isempty(char *line)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] == ' ')
			k++;
		i++;
	}
	if (i == k)
		return (1);
	return (0);
}

void	lines_count(char **av, t_cub *cub)
{
	cub->fd = open(av[1], O_RDONLY);
	if (cub->fd <= 0)
	{
		perror("error: cannot open the map");
		exit(1);
	}
	cub->line = get_next_line(cub->fd);
	while (cub->line)
	{
		line_mod(cub);
		if (!cub->mapstart && ismap(cub->line))
			cub->mapstart = cub->lines;
		if (!cub->mapend && cub->mapstart && isempty(cub->line))
			cub->mapend = cub->lines;
		free(cub->line);
		cub->line = get_next_line(cub->fd);
		cub->lines++;
	}
	if (!cub->mapend && cub->mapstart)
		cub->mapend = cub->lines;
	if (cub->mapend <= cub->mapstart)
		pars_free(cub, 1);
	close(cub->fd);
	cub->lines = cub->mapend - cub->mapstart;
}

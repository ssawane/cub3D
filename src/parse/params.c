/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssawane <ssawane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 10:24:08 by ssawane           #+#    #+#             */
/*   Updated: 2022/08/12 23:13:55 by ssawane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	texture_check(t_cub *cub)
{
	int	i;
	int	fd;

	i = ft_strlen(cub->par[1]) - 1;
	if (i < 4 || cub->par[1][i] != 'm' || cub->par[1][i - 1] != 'p'
		|| cub->par[1][i - 2] != 'x' || cub->par[1][i - 3] != '.')
		pars_free(cub, 1);
	fd = open(cub->par[1], O_RDONLY);
	if (fd < 0)
		pars_free(cub, 1);
	close(fd);
	if (!ft_strncmp(cub->par[0], "NO", 2) && !cub->game->no)
		cub->game->no = ft_strdup(cub->par[1]);
	else if (!ft_strncmp(cub->par[0], "SO", 2) && !cub->game->so)
		cub->game->so = ft_strdup(cub->par[1]);
	else if (!ft_strncmp(cub->par[0], "WE", 2) && !cub->game->we)
		cub->game->we = ft_strdup(cub->par[1]);
	else if (!ft_strncmp(cub->par[0], "EA", 2) && !cub->game->ea)
		cub->game->ea = ft_strdup(cub->par[1]);
	else
		pars_free(cub, 1);
	cub->infos++;
}

void	param_add(t_cub *cub, int type)
{
	cub->par = ft_split(cub->line, ' ');
	if (type == 1)
	{
		if (cub->par[1] && !cub->par[2])
			texture_check(cub);
		else if (cub->par[2])
			pars_free(cub, 1);
	}
	else
		color_check(cub, type);
	free_mass(cub->par);
	cub->par = NULL;
}

char	*tabs_change(t_cub *cub, int k, int i)
{
	char	*res;

	res = (char *)malloc(sizeof(char) * (ft_strlen(cub->line) + (k * 3)));
	if (!res)
		pars_free(cub, 1);
	k = 0;
	while (cub->line[i])
	{
		if (cub->line[i] == '\t')
		{
			res[k++] = ' ';
			res[k++] = ' ';
			res[k++] = ' ';
			res[k++] = ' ';
			i++;
		}
		else
			res[k++] = cub->line[i++];
	}
	res[k] = '\0';
	return (res);
}

void	line_mod(t_cub *cub)
{
	int		i;
	int		k;
	char	*tmp;

	i = -1;
	k = 0;
	if (cub->line[ft_strlen(cub->line) - 1] == '\n')
	{
		tmp = cub->line;
		cub->line = ft_substr(cub->line, 0, ft_strlen(cub->line) - 1);
		free(tmp);
	}
	while (cub->line[++i])
		if (cub->line[i] == '\t')
			k++;
	if (k > 0)
	{
		i = 0;
		tmp = cub->line;
		cub->line = tabs_change(cub, k, i);
		free(tmp);
	}
}

void	params(t_cub *cub)
{
	line_mod(cub);
	if (!isempty(cub->line) && !ismap(cub->line))
	{
		if (!ft_strncmp(cub->line, "NO ", 3)
				|| !ft_strncmp(cub->line, "SO ", 3)
				|| !ft_strncmp(cub->line, "WE ", 3)
				|| !ft_strncmp(cub->line, "EA ", 3))
			param_add(cub, 1);
		else if (!ft_strncmp(cub->line, "F ", 2))
			param_add(cub, 2);
		else if (!ft_strncmp(cub->line, "C ", 2))
			param_add(cub, 3);
		else
			pars_free(cub, 1);
	}
	free(cub->line);
}
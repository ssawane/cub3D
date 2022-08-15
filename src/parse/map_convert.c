/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_convert.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssawane <ssawane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 22:37:43 by ssawane           #+#    #+#             */
/*   Updated: 2022/08/13 11:58:04 by ssawane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	change_map(t_cub *cub)
{
	int		i;
	int		j;
	char	**tmp;

	i = -1;
	tmp = malloc(sizeof(char *) * cub->lines + 1);
	while (cub->game->map[++i])
	{
		if (ft_strlen(cub->game->map[i]) < cub->len)
		{
			j = -1;
			tmp[i] = malloc(sizeof(char) * cub->len);
			while (cub->game->map[i][++j])
				tmp[i][j] = cub->game->map[i][j];
			while (j < cub->len)
				tmp[i][j++] = ' ';
			tmp[i][j] = '\0';
		}
		else
			tmp[i] = ft_strdup(cub->game->map[i]);
	}
	tmp[i] = 0;
	free_mass(cub->game->map);
	cub->game->map = tmp;
}

void	corners_check(char **map, t_cub *cub)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] != '1' && map[i][j] != ' ')
			{
				if (i == 0 || i == cub->lines - 1
					|| j == 0 || j == cub->len - 1)
					pars_free(cub, 2);
				if (map[i - 1][j - 1] == ' '
					|| map[i - 1][j + 1] == ' '
					|| map[i + 1][j - 1] == ' '
					|| map[i + 1][j + 1] == ' ')
					pars_free(cub, 2);
			}
		}
	}
}

void	valid_symbs(char **map, t_cub *cub)
{
	int	i;
	int	j;
	int	flag;

	i = -1;
	flag = 0;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] != '1' && map[i][j] != '0'
				&& map[i][j] != 'N' && map[i][j] != 'S'
				&& map[i][j] != 'W' && map[i][j] != 'E'
				&& map[i][j] != ' ')
				pars_free(cub, 2);
			if (map[i][j] == 'N' || map[i][j] == 'S'
				|| map[i][j] == 'W' || map[i][j] == 'E')
				flag++;
		}
	}
	if (flag != 1)
		pars_free(cub, 2);
}

void	map_checks(t_cub *cub)
{
	if (cub->nosquare)
		change_map(cub);
	valid_symbs(cub->game->map, cub);
	borders_check(cub->game->map, cub);
	corners_check(cub->game->map, cub);
}

void	map_convert(t_cub *cub, int i)
{
	int		k;

	k = 0;
	cub->game->map = malloc(sizeof(char *) * (cub->lines + 1));
	if (!cub->game->map)
		pars_free(cub, 2);
	while (i <= cub->mapend)
	{
		cub->line = get_next_line(cub->fd);
		line_mod(cub);
		if (!isempty(cub->line))
			cub->game->map[k++] = ft_strdup(cub->line);
		if (ft_strlen(cub->line) != cub->len)
		{
			if (cub->len)
				cub->nosquare = 1;
			if (ft_strlen(cub->line) > cub->len)
				cub->len = ft_strlen(cub->line);
		}
		free(cub->line);
		cub->line = NULL;
		i++;
	}
	cub->game->map[k] = 0;
}

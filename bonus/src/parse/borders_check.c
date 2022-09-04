/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   borders_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssawane <ssawane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 20:50:42 by ssawane           #+#    #+#             */
/*   Updated: 2022/08/28 10:34:06 by ssawane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	spc_val(char c)
{
	if (c == ' ' || c == '1')
		return (1);
	return (0);
}

void	borders_check_next2(t_cub *cub, char **map, int i, int j)
{
	if (j == cub->len - 1)
	{
		if (!spc_val(map[i][j - 1]) || !spc_val(map[i - 1][j])
			|| !spc_val(map[i + 1][j]))
			pars_free(cub, 2);
	}
	else if (i == 0)
	{
		if (!spc_val(map[i][j + 1]) || !spc_val(map[i][j - 1])
			|| !spc_val(map[i + 1][j]))
			pars_free(cub, 2);
	}
	else if (i == cub->lines - 1)
	{
		if (!spc_val(map[i][j + 1]) || !spc_val(map[i][j - 1])
			|| !spc_val(map[i - 1][j]))
			pars_free(cub, 2);
	}
	else
	{
		if (!spc_val(map[i][j + 1]) || !spc_val(map[i][j - 1])
			|| !spc_val(map[i + 1][j]) || !spc_val(map[i - 1][j]))
			pars_free(cub, 2);
	}
}

void	borders_check_next(t_cub *cub, char **map, int i, int j)
{
	if (j == 0 && i == cub->lines - 1)
	{
		if (!spc_val(map[i][j + 1]) || !spc_val(map[i - 1][j]))
			pars_free(cub, 2);
	}
	else if (j == cub->len - 1 && i == 0)
	{
		if (!spc_val(map[i][j - 1]) || !spc_val(map[i + 1][j]))
			pars_free(cub, 2);
	}
	else if (j == cub->len - 1 && i == cub->lines - 1)
	{
		if (!spc_val(map[i][j - 1]) || !spc_val(map[i - 1][j]))
			pars_free(cub, 2);
	}
	else if (j == 0)
	{
		if (!spc_val(map[i][j + 1]) || !spc_val(map[i - 1][j])
			|| !spc_val(map[i + 1][j]))
			pars_free(cub, 2);
	}
	else
		borders_check_next2(cub, map, i, j);
}

void	borders_check(char **map, t_cub *cub)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == ' ')
			{
				if (j == 0 && i == 0)
				{
					if (!spc_val(map[i][j + 1]) || !spc_val(map[i + 1][j]))
						pars_free(cub, 2);
				}
				else
					borders_check_next(cub, map, i, j);
			}
		}
	}
}

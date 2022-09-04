/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssawane <ssawane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 14:35:56 by ssawane           #+#    #+#             */
/*   Updated: 2022/08/28 10:38:03 by ssawane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	isdigs(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] < 48 || str[i] > 57)
			return (0);
	}
	return (1);
}

void	spaces_del(t_cub *cub, char *tmp, int k)
{
	int		i;

	free(cub->line);
	cub->line = (char *)malloc(sizeof(char) * (ft_strlen(tmp) - k));
	if (!cub->line)
		pars_free(cub, 1);
	i = 0;
	k = 0;
	while (tmp[i])
	{
		if (tmp[i] != ' ')
			cub->line[k++] = tmp[i++];
		else
			i++;
	}
	cub->line[k] = '\0';
	free(tmp);
}

void	commas_check(t_cub *cub)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (cub->line[i])
	{
		if (cub->line[i] == ',')
			k++;
		i++;
	}
	if (k != 2)
		pars_free(cub, 1);
}

void	color_next(t_cub *cub, int type, int i)
{
	i = -1;
	cub->clrs = ft_split(cub->line, ',');
	if (cub->clrs[0] && cub->clrs[1]
		&& cub->clrs[2] && !cub->clrs[3])
	{
		while (cub->clrs[++i])
		{
			cub->clr = ft_atoi(cub->clrs[i]);
			if (isdigs(cub->clrs[i]) && cub->clr >= 0 && cub->clr <= 255)
			{
				if (type == 2)
					cub->game->floor[i] = cub->clr;
				else if (type == 3)
					cub->game->ceiling[i] = cub->clr;
			}
			else
				pars_free(cub, 1);
		}
		free_mass(cub->clrs);
		cub->clrs = NULL;
	}
	else
		pars_free(cub, 1);
}

void	color_check(t_cub *cub, int type)
{
	int		i;
	int		k;
	char	*tmp;

	i = -1;
	k = 0;
	tmp = ft_substr(cub->line, 2, ft_strlen(cub->line) - 2);
	while (tmp[++i])
		if (tmp[i] == ' ')
			k++;
	if (k > 0)
		spaces_del(cub, tmp, k);
	else
	{
		free(cub->line);
		cub->line = tmp;
	}
	commas_check(cub);
	color_next(cub, type, i);
	cub->infos++;
}

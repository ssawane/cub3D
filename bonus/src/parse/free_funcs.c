/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssawane <ssawane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 14:34:46 by ssawane           #+#    #+#             */
/*   Updated: 2022/09/04 14:44:52 by ssawane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	free_mass(char **mass)
{
	int	i;

	i = -1;
	while (mass[++i])
		free(mass[i]);
	free(mass);
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

void	free_memory(t_cub *cub)
{
	printf("bad line: %s\n", cub->line); // delete
	if (cub->game->no)
		free(cub->game->no);
	if (cub->game->so)
		free(cub->game->so);
	if (cub->game->we)
		free(cub->game->we);
	if (cub->game->ea)
		free(cub->game->ea);
	if (cub->game->dr)
		free(cub->game->dr);
	if (cub->game->gn)
		free(cub->game->gn);
	if (cub->game->map)
		free_mass(cub->game->map);
	if (cub->par)
		free_mass(cub->par);
	if (cub->clrs)
		free_mass(cub->clrs);
	if (cub->line)
		free(cub->line);
	close(cub->fd);
}

void	pars_free(t_cub *cub, int flag)
{
	free_memory(cub);
	if (flag == 1)
		printf("%s\n", "error: bad params");
	if (flag == 2)
		printf("%s\n", "error: bad map");
	// while (1);
	exit(1);
}

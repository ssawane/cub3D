/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssawane <ssawane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 14:34:46 by ssawane           #+#    #+#             */
/*   Updated: 2022/09/05 15:37:48 by ssawane          ###   ########.fr       */
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

void	pars_free(t_cub *cub, int flag)
{
	if (cub->game->no)
		free(cub->game->no);
	if (cub->game->so)
		free(cub->game->so);
	if (cub->game->we)
		free(cub->game->we);
	if (cub->game->ea)
		free(cub->game->ea);
	if (cub->game->map)
		free_mass(cub->game->map);
	if (cub->par)
		free_mass(cub->par);
	if (cub->clrs)
		free_mass(cub->clrs);
	if (cub->line)
		free(cub->line);
	close(cub->fd);
	if (flag == 1)
		printf("%s\n", "error: bad params");
	if (flag == 2)
		printf("%s\n", "error: bad map");
	exit(1);
}

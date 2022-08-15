/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssawane <ssawane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 17:11:33 by ssawane           #+#    #+#             */
/*   Updated: 2022/08/12 11:08:25 by ssawane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	print_params(t_game *game)
{
	int	i;
	
	printf("NORTH: %s\n", game->no);
	printf("SOUTH: %s\n", game->so);
	printf("WEST: %s\n", game->we);
	printf("EAST: %s\n", game->ea);
	i = -1;
	while (++i < 3)
		printf("floor %d: %d\n", i, game->floor[i]);
	i = -1;
	while (++i < 3)
		printf("ceiling %d: %d\n", i, game->ceiling[i]);
}

void	print_map(t_game *game)
{
	int	i;

	i = -1;
	if (game->map)
	{
		while (game->map[++i])
		{
			printf("%s\n", game->map[i]);
		}
	}
}
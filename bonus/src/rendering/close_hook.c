/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssawane <ssawane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 10:30:10 by ssawane           #+#    #+#             */
/*   Updated: 2022/09/05 15:21:57 by ssawane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	close_win(void)
{
	exit (0);
}

void	escape(int keycode, t_game *game)
{
	if (keycode == ESC)
	{
		mlx_destroy_window(game->mlx, game->mlx_win);
		exit(0);
	}
}

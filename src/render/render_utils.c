/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 09:53:27 by ael-mank          #+#    #+#             */
/*   Updated: 2024/09/29 10:15:39 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	create_tiles(t_tile **tiles, int *tile_count, int width, int height,
		int tile_size)
{
	int	num_x_tiles;
	int	num_y_tiles;
	int	index;
	int	y;
	int	x;

	num_x_tiles = (width + tile_size - 1) / tile_size;
	num_y_tiles = (height + tile_size - 1) / tile_size;
	*tile_count = num_x_tiles * num_y_tiles;
	*tiles = malloc(*tile_count * sizeof(t_tile));
	y = 0;
	while (y < num_y_tiles)
	{
		x = 0;
		while (x < num_x_tiles)
		{
			index = y * num_x_tiles + x;
			(*tiles)[index].x_start = x * tile_size;
			if ((x + 1) * tile_size > width)
				(*tiles)[index].x_end = width;
			else
				(*tiles)[index].x_end = (x + 1) * tile_size;
			(*tiles)[index].y_start = y * tile_size;
			if ((y + 1) * tile_size > height)
				(*tiles)[index].y_end = height;
			else
				(*tiles)[index].y_end = (y + 1) * tile_size;
			x++;
		}
		y++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 13:52:28 by ael-mank          #+#    #+#             */
/*   Updated: 2024/09/29 13:55:33 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static inline void	set_tile_bounds(t_tile *tile, int x, int y,
		t_tile_params *params)
{
	tile->x_start = x * params->tile_size;
	if ((x + 1) * params->tile_size > params->width)
		tile->x_end = params->width;
	else
		tile->x_end = (x + 1) * params->tile_size;
	tile->y_start = y * params->tile_size;
	if ((y + 1) * params->tile_size > params->height)
		tile->y_end = params->height;
	else
		tile->y_end = (y + 1) * params->tile_size;
}

static inline void	allocate_tiles(t_tile **tiles, int *tile_count,
		int num_x_tiles, int num_y_tiles)
{
	*tile_count = num_x_tiles * num_y_tiles;
	*tiles = malloc(*tile_count * sizeof(t_tile));
}

void	create_tiles(t_tile **tiles, int *tile_count, t_tile_params *params)
{
	int	ints[4];

	ints[0] = (params->width + params->tile_size - 1) / params->tile_size;
	ints[1] = (params->height + params->tile_size - 1) / params->tile_size;
	allocate_tiles(tiles, tile_count, ints[0], ints[1]);
	ints[2] = 0;
	while (ints[2] < ints[1])
	{
		ints[3] = 0;
		while (ints[3] < ints[0])
		{
			set_tile_bounds(&(*tiles)[ints[2] * ints[0] + ints[3]], ints[3],
				ints[2], params);
			ints[3]++;
		}
		ints[2]++;
	}
}

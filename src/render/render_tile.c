/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_tile.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 09:53:04 by ael-mank          #+#    #+#             */
/*   Updated: 2024/09/29 09:53:08 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	*render_tile(void *arg)
{
	t_render_params	*params;
	t_scene			*scene;
	int				tile_index;
	t_tile			tile;
	t_vec3			color;
	t_ray			r;
	int				j;
	int				i;
	int				sample;

	params = (t_render_params *)arg;
	scene = params->scene;
	while (1)
	{
		tile_index = __sync_fetch_and_add(params->next_tile, 1);
		if (tile_index >= params->tile_count)
			break ;
		tile = params->tiles[tile_index];
		j = tile.y_start;
		while (j < tile.y_end)
		{
			i = tile.x_start;
			while (i < tile.x_end)
			{
				color = vec3(0, 0, 0);
				sample = 0;
				while (sample < scene->camera.samples_per_pixel)
				{
					r = get_ray(i, j, &scene->camera);
					color = vector_add(color, ray_color(&r,
								scene->camera.max_depth, scene->bvh, scene));
					sample++;
				}
				write_colors(&scene->mlx.img, i, j, color);
				i++;
			}
			j++;
		}
	}
	return (NULL);
}

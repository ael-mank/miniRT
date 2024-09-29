/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_tile.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 09:53:04 by ael-mank          #+#    #+#             */
/*   Updated: 2024/09/29 13:56:57 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static inline void	render_pixel(t_scene *scene, t_vec3 *color, int *ints)
{
	t_ray	r;

	*color = vec3(0, 0, 0);
	ints[3] = 0;
	while (ints[3] < scene->camera.samples_per_pixel)
	{
		r = get_ray(ints[2], ints[1], &scene->camera);
		*color = vector_add(*color, ray_color(&r, scene->camera.max_depth,
					scene->bvh, scene));
		ints[3]++;
	}
	write_colors(&scene->mlx.img, ints[2], ints[1], *color);
}

static inline void	render_tile_section(t_scene *scene, t_tile tile)
{
	t_vec3	color;
	int		ints[4];

	ints[1] = tile.y_start;
	while (ints[1] < tile.y_end)
	{
		ints[2] = tile.x_start;
		while (ints[2] < tile.x_end)
		{
			render_pixel(scene, &color, ints);
			ints[2]++;
		}
		ints[1]++;
	}
}

void	*render_tile(void *arg)
{
	t_render_params	*params;
	t_scene			*scene;
	t_tile			tile;
	int				tile_index;

	params = (t_render_params *)arg;
	scene = params->scene;
	while (1)
	{
		tile_index = __sync_fetch_and_add(params->next_tile, 1);
		if (tile_index >= params->tile_count)
			break ;
		tile = params->tiles[tile_index];
		render_tile_section(scene, tile);
	}
	return (NULL);
}

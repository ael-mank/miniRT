/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 10:00:00 by ael-mank          #+#    #+#             */
/*   Updated: 2024/09/29 13:55:13 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static inline void	initialize_params(t_init_params *init_params,
										pthread_t *threads)
{
	int	t;

	t = 0;
	while (t < NUM_THREADS)
	{
		init_params->params[t].scene = init_params->scene;
		init_params->params[t].tiles = init_params->tiles;
		init_params->params[t].tile_count = init_params->tile_count;
		init_params->params[t].next_tile = init_params->next_tile;
		pthread_create(&threads[t], NULL, render_tile, &init_params->params[t]);
		t++;
	}
}

static inline void	join_threads(pthread_t *threads)
{
	int	t;

	t = 0;
	while (t < NUM_THREADS)
	{
		pthread_join(threads[t], NULL);
		t++;
	}
}

void	render_scene(t_scene *scene)
{
	t_render_data	render_data;
	struct timeval	times[2];
	t_init_params	init_params;
	t_tile_params	tile_params;

	render_data.ints[1] = 0;
	tile_params = (t_tile_params){scene->render.image_width,
		scene->render.image_height, TILE_SIZE};
	create_tiles(&render_data.tiles, &render_data.ints[0], &tile_params);
	gettimeofday(&times[0], NULL);
	init_params = (t_init_params){render_data.params, scene, render_data.tiles,
		render_data.ints[0], &render_data.ints[1]};
	initialize_params(&init_params, render_data.threads);
	join_threads(render_data.threads);
	gettimeofday(&times[1], NULL);
	printf("Time to render: %.2f seconds\n", ((times[1].tv_sec
				- times[0].tv_sec) + (times[1].tv_usec - times[0].tv_usec)
			/ 1e6));
	free(render_data.tiles);
	mlx_put_image_to_window(scene->mlx.mlx_ptr, scene->mlx.win_ptr,
		scene->mlx.img.img, 0, 0);
}

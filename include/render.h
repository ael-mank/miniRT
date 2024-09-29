/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 09:51:19 by ael-mank          #+#    #+#             */
/*   Updated: 2024/09/29 10:11:59 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "minirt.h"
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

# define EPSILON 1e-4
# define NUM_THREADS 20
# define TILE_SIZE 64

typedef struct s_tile
{
	int				x_start;
	int				x_end;
	int				y_start;
	int				y_end;
}					t_tile;

typedef struct s_render_params
{
	t_scene			*scene;
	t_tile			*tiles;
	int				tile_count;
	int				*next_tile;
}					t_render_params;

typedef struct s_render_data
{
	pthread_t		threads[NUM_THREADS];
	t_render_params	params[NUM_THREADS];
	t_tile			*tiles;
	int				ints[3];
}					t_render_data;

typedef struct s_init_params
{
	t_render_params	*params;
	t_scene			*scene;
	t_tile			*tiles;
	int				tile_count;
	int				*next_tile;
}					t_init_params;

t_vec3				calculate_lighting(t_hitrecord *rec, t_scene *scene);
t_vec3				ray_color(t_ray *r, int depth, t_bvh *bvh, t_scene *scene);
t_vec3				defocus_disk_sample(t_camera *camera);
t_ray				get_ray(int i, int j, t_camera *camera);
void				*render_tile(void *arg);
void				create_tiles(t_tile **tiles, int *tile_count, int width,
						int height, int tile_size);
void				render_scene(t_scene *scene);

#endif
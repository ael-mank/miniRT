/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 08:42:36 by ael-mank          #+#    #+#             */
/*   Updated: 2024/08/14 15:46:27 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "interval.h"
# include "libft.h"
# include "mlx.h"
# include "my_mlx.h"
# include "objects.h"
# include "vectors.h"
# include <X11/keysym.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <unistd.h>

extern FILE		*out;

// Structs
typedef struct s_render
{
	double		aspect_ratio;
	int			image_width;
	int			image_height;
}				t_render;

typedef struct s_camera
{
	double		focal_length;
	double		viewport_height;
	double		viewport_width;
	t_point3	camera_center;
	t_vec3		viewport_u;
	t_vec3		viewport_v;
	t_vec3		pixel_delta_u;
	t_vec3		pixel_delta_v;
	t_point3	viewport_upper_left;
	t_point3	pixel00_loc;
	int			samples_per_pixel;
	int			max_depth;
}				t_camera;

typedef struct s_scene
{
	t_mlx		mlx;
	t_camera	camera;
	t_render	render;
	t_ray		r;
	t_object	*objects;
}				t_scene;

// Memory management
int				ft_exit(t_scene *scene);
void			free_scene(t_object *objects);

// Window, mlx stuff
int				keys_handler(int key_code, t_scene *scene);

// Initialization
void			init_camera(t_camera *camera);
t_object		*init_objects(void);
void			init_mlx(t_scene *scene, int win_width, int win_height);
void			init_render(t_render *render);
void			init_scene(t_scene *scene);
void			init_viewport(t_camera *camera, t_render *render);

// Rendering
void			render_scene(t_scene *scene);

// Utility
double			deg_to_rad(double degrees);
double			ft_fmin(double a, double b);
double			rand_double(double min, double max);
double			random_double(void);

#endif
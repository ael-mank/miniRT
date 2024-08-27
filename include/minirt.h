/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrigny <yrigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 08:42:36 by ael-mank          #+#    #+#             */
/*   Updated: 2024/08/27 20:06:19 by yrigny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# define LENGTH 800
# define HEIGHT 600
# define F_LENGTH 1.0
# define PI 3.1415927
# include "libft.h"
# include "mlx.h"
# include "struct.h"
# include <X11/keysym.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <unistd.h>
# include <stdbool.h>

// event
int	win_close(t_win *e);
int	key_event(int key, t_win *e);

// setting
void		win_init(t_win *win, t_scene *scene);
void		scene_init(t_scene *scene);
t_light		light_init();
t_ambient	ambient_init();
t_cam		cam_init();
t_viewport	viewport_init(t_cam cam);
t_sphere	sphere_init();
t_plane		plane_init();

// vec_helper
t_vec3	vec3(double x, double y, double z);
t_vec3	vector_add(t_vec3 a, t_vec3 b);
t_vec3	vector_subtract(t_vec3 a, t_vec3 b);
t_vec3	vector_scale(t_vec3 v, double scalar);
double	dot_product(t_vec3 a, t_vec3 b);
t_vec3	cross_product(t_vec3 a, t_vec3 b);
double	vector_length(t_vec3 v);
t_vec3	vector_normalize(t_vec3 v);
void	print_vec3(t_vec3 v);

// color_helper
t_color	color(int r, int g, int b);
t_color	color_scale(t_color base, double scaler);
t_color	color_add(t_color a, t_color b);

// raytracing
int				calculate_image(t_win *win);
unsigned int	calculate_pixel(int x, int y, t_scene scene);
t_point3	find_pixel_on_viewport(int x, int y, t_viewport v);
t_ray	init_ray(t_cam c, t_point3 pixel);
void	cast_ray(t_ray *ray, t_scene *scene);
void	intersect_sphere(t_ray *ray, t_cam cam, t_sphere *s);
void	intersect_plane(t_ray *ray, t_cam cam, t_plane *pl);
t_color	ray_color(t_ray ray, t_scene scene);
t_color	weighted_obj_color(t_ray *ray, void *obj, t_light l);
double	light_weight(t_ray *ray, void *obj, t_light l);

#endif

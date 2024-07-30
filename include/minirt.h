/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrigny <yrigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 08:42:36 by ael-mank          #+#    #+#             */
/*   Updated: 2024/07/30 17:36:32 by yrigny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# define LENGTH 800
# define HEIGHT 600
# define F_LENGTH 1.0
# include "libft.h"
# include "mlx.h"
# include "struct.h"
# include <X11/keysym.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <unistd.h>

// event
int	win_close(t_win *e);
int	key_event(int key, t_win *e);

// setting
void	win_init(t_win *win, t_scene *scene);
void	scene_init(t_scene *scene);
t_light	light_init();
t_cam	cam_init();
t_viewport	viewport_init(t_cam cam);
t_sphere	sphere_init();

// vec_helper
t_vec3	vec3(double x, double y, double z);
t_vec3	vector_add(t_vec3 a, t_vec3 b);
t_vec3	vector_subtract(t_vec3 a, t_vec3 b);
t_vec3	vector_scale(t_vec3 v, double scalar);
double	dot_product(t_vec3 a, t_vec3 b);
t_vec3	cross_product(t_vec3 a, t_vec3 b);
double	vector_length(t_vec3 v);
t_vec3	vector_normalize(t_vec3 v);

// color_helper
t_color	color(unsigned char r, unsigned char g, unsigned char b);

// raytracing
int	calculate_image(t_win *win);
unsigned int	calculate_pixel(int x, int y, t_scene scene);


#endif
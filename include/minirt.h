/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrigny <yrigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 08:42:36 by ael-mank          #+#    #+#             */
/*   Updated: 2024/09/19 16:53:48 by yrigny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# define LENGTH 800
# define HEIGHT 600
# define F_LENGTH 1.0
# define PI 3.1415927
# define NO_HIT 0
# define TRUE_HIT 1
# define FALSE_HIT -1
# define INTEGER 1
# define FLOAT 2
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
void	free_scene(t_scene *scene);

// parse
void	parse_rt(t_scene *scene, int ac, char **av);
int	try_open_file(int ac, char **av);
bool	parse_element(t_scene *scene, char *element);
bool	parse_and_add_camera(char *line, t_scene *scene);
void	init_viewport(t_cam *cam);
bool	parse_and_add_ambient(char *line, t_scene *scene);
bool	parse_and_add_light(char *line, t_scene *scene);
bool    parse_and_add_plane(char *line, t_scene *scene);
bool    parse_and_add_sphere(char *line, t_scene *scene);
bool	parse_and_add_cylinder(char *line, t_scene *scene);
bool	parse_ratio(char **line, double *ratio);
bool	parse_color(char **line, t_color *color);
bool	parse_point(char **line, t_vec3 *point);
bool	parse_direction(char **line, t_vec3 *vec);
bool	parse_fov(char **line, double *fov);
bool    parse_length(char **line, double *length);

void	add_to_obj_list(void *obj, t_scene *scene, t_obj_type type);
// void	add_obj_back(t_obj **lst, t_obj *new);

// parse_helper
bool	is_float_format(char *s);
int		count_parts(char *s, char c);
bool	str_is_int(char *s);
bool	str_is_digit(char *s);
double	ft_atof(char *s);
bool	is_vec3_format(char *s, int type);
t_color	ft_atorgb(char *s);
t_vec3	ft_atovec3(char *s);



// setting
void		win_init(t_win *win, t_scene *scene);
// // void		scene_init(t_scene *scene);
// t_light		light_init();
// t_ambient	ambient_init();
// t_cam		cam_init();
// t_viewport	viewport_init(t_cam cam);
// t_sphere	sphere_init();
// t_plane		plane_init();
// t_cylinder	cylinder_init();

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
unsigned int	calculate_pixel(int x, int y, t_scene *scene);
t_point3	find_pixel_on_viewport(int x, int y, t_viewport v);
t_ray	init_ray(t_cam *c, t_point3 pixel);
void	cast_ray(t_ray *ray, t_scene *scene);

// intersecting
void	solve_equation(t_root *res, double a, double b, double c);
void	intersect_sphere(t_ray *ray, t_cam cam, t_sphere *s);
void	intersect_plane(t_ray *ray, t_cam cam, t_plane *pl);
void	intersect_cylinder_front(t_ray *ray, t_cam cam, t_cylinder *cy);
void	intersect_cylinder_back(t_ray *ray, t_cam cam, t_cylinder *cy);
bool	in_cylinder_limit(double root, t_cam c, t_ray *ray, t_cylinder *cy);

// ray_coloring
t_color	ray_color(t_ray *ray, t_scene *scene);
t_color	weighted_obj_color(t_ray *ray, void *obj, t_light *l);
double	light_weight(t_ray *ray, void *obj, t_light *l);

#endif

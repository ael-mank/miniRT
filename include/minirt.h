/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 08:42:36 by ael-mank          #+#    #+#             */
/*   Updated: 2024/09/05 11:59:33 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "aabb.h"
# include "bvh.h"
# include "interval.h"
# include "libft.h"
# include "mlx.h"
# include "mlx_int.h"
# include "my_mlx.h"
# include "objects.h"
# include "vectors.h"
# include <X11/keysym.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <unistd.h>

//extern FILE		*out;

// Structs
typedef struct s_render
{
	double			aspect_ratio;
	int				image_width;
	int				image_height;
}					t_render;

typedef struct s_camera
{
	double			focus_dist;
	double			defocus_angle;
	t_vec3			defocus_disk_u;
	t_vec3			defocus_disk_v;
	double			viewport_height;
	double			viewport_width;
	double			fov;
	double			theta;
	t_point3		camera_center;
	t_point3		lookfrom;
	t_point3		lookat;
	t_point3		u;
	t_point3		v;
	t_point3		w;
	t_vec3			v_up;
	t_vec3			viewport_u;
	t_vec3			viewport_v;
	t_vec3			pixel_delta_u;
	t_vec3			pixel_delta_v;
	t_point3		viewport_upper_left;
	t_point3		pixel00_loc;
	int				samples_per_pixel;
	int				max_depth;
}					t_camera;

typedef struct s_render_info
{
	t_vec3			color;
	int				sample;
	t_ray			r;
	int				i;
	int				j;
}					t_render_info;

typedef struct s_scene
{
	t_mlx			mlx;
	t_camera		camera;
	t_render		render;
	t_ray			r;
	t_object		*objects;
	t_bvh			*bvh;
	t_vec3			bg_color;
	t_render_info	rdr;
	int				file_fd;
	t_list			*lst_map;
	int				mouse_mode;
}					t_scene;


void *get_mlx_ptr(void);
// Memory management
int					ft_exit(t_scene *scene);
//void				free_scene(t_object *objects);

// Window, mlx stuff
int					keys_handler(int key_code, t_scene *scene);

// Initialization
void				parse_file(t_scene *scene, char **argv);
int					parse_ambient(t_scene *scene, char *line);
void				init_camera(t_camera *camera);
t_object			*init_objects(void);
t_material			*create_material(t_material_type type);
t_object			*add_object_end(t_object *head, t_object *new_object);
void				init_mlx(t_scene *scene, int win_width, int win_height);
void				init_render(t_render *render);
void	init_scene(t_scene *scene, char **argv);
void				init_viewport(t_camera *camera, t_render *render);

// Rendering
void				render_scene(t_scene *scene);

// Utility
double				deg_to_rad(double degrees);
double				ft_fmin(double a, double b);
double				rand_double(double min, double max);
double				random_double(void);
void	ft_error(t_scene *scene, char *msg);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrigny <yrigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 17:13:48 by yrigny            #+#    #+#             */
/*   Updated: 2024/09/23 17:11:57 by yrigny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H
# include <stdbool.h>

typedef enum e_obj_type
{
	DEFAULT,
	SPHERE,
	PLANE,
	CYLINDER,
	CYLINDER_E,
	CYLINDER_I,
}	t_obj_type;

typedef struct s_obj	t_obj;
typedef	struct s_vec3	t_point3;
typedef	struct s_vec3	t_vec3;
typedef	struct s_color	t_color;
typedef struct s_ray	t_ray;
typedef struct s_viewport	t_viewport;
typedef struct s_cam	t_cam;
typedef struct s_light	t_light;
typedef struct s_ambient	t_ambient;
typedef struct s_sphere	t_sphere;
typedef struct s_plane	t_plane;
typedef struct s_cylinder	t_cylinder;
typedef struct s_img	t_img;
typedef struct s_scene	t_scene;
typedef struct s_win	t_win;

typedef struct s_obj
{
	t_obj_type		type;
	void			*obj;
	struct s_obj	*next;	
}	t_obj;

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;

typedef struct s_ray
{
	t_point3	org;
	t_vec3		dir;
	int			hit_object;
	t_obj_type	object_type;
	void		*object;
	double		hit_distance;
	t_point3	intersect;
}	t_ray;

typedef struct s_viewport
{
	double	w;
	double	h;
	t_vec3	u;
	t_vec3	v;
	t_vec3	pixel_delta_u;
	t_vec3	pixel_delta_v;
	t_point3	upperleft;
	t_point3	pixel00;
}	t_viewport;

typedef struct s_cam
{
	t_point3	org;
	t_vec3		dir;
	double		fov;
	double		theta_radian;
	t_viewport	v;
}	t_cam;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_light
{
	t_point3	org;
	double		ratio;
	t_color		color;
}	t_light;

typedef struct s_ambient
{
	double	ratio;
	t_color	color;
}	t_ambient;

typedef struct s_sphere
{
	t_point3	center;
	double		diameter;
	double		radius;
	t_color		color;
}	t_sphere;

typedef struct s_plane
{
	t_point3	point;
	t_vec3		normal;
	t_color		color;
}	t_plane;

typedef struct s_cylinder
{
	t_point3	center;
	t_vec3		axis;
	double		diameter;
	double		radius;
	double		height;
	t_color		color;
}	t_cylinder;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_scene
{
	t_ambient	*a;
	t_light		*l;
	t_cam		*c;
	t_obj		*objs;
}	t_scene;

typedef struct s_win
{
	void			*mlx;
	void			*mlx_win;
	t_scene			*scene;
	t_img			img;
	int				render;
}	t_win;

typedef struct s_root
{
	double	delta;
	int		hit;
	double	root1;
	double	root2;
}	t_root;

#endif

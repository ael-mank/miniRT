/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrigny <yrigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 17:13:48 by yrigny            #+#    #+#             */
/*   Updated: 2024/07/30 17:40:03 by yrigny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef	struct s_vec3	t_point3;
typedef	struct s_vec3	t_vec3;
typedef	struct s_color	t_color;
typedef struct s_ray	t_ray;
typedef struct s_cam	t_cam;
typedef struct s_viewport	t_viewport;
typedef struct s_light	t_light;
typedef struct s_ambient	t_ambient;
typedef struct s_sphere	t_sphere;

typedef struct s_img	t_img;
typedef struct s_scene	t_scene;
typedef struct s_win	t_win;

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
}	t_ray;

typedef struct s_cam
{
	t_point3	org;
	t_vec3		dir;
	double		fov;
}	t_cam;

typedef struct s_viewport
{
	double	l;
	double	h;
	t_vec3	u;
	t_vec3	v;
	t_vec3	pixel_delta_u;
	t_vec3	pixel_delta_v;
}	t_viewport;

typedef struct s_color
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
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
	double		radius;
	t_color		color;
}	t_sphere;

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
	// t_ambient	a;
	t_light		l;
	t_cam		c;
	t_viewport	v;
	// t_list		*objs;
	t_sphere	sp;
}	t_scene;

typedef struct s_win
{
	void			*mlx;
	void			*mlx_win;
	t_scene			*scene;
	t_img			img;
	int				render;
}	t_win;


#endif

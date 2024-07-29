/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrigny <yrigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 17:13:48 by yrigny            #+#    #+#             */
/*   Updated: 2024/07/29 17:41:06 by yrigny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef	struct s_vec3	t_point3;
typedef	struct s_vec3	t_vec3;
typedef struct s_ray	t_ray;
typedef struct s_cam	t_cam;
typedef struct s_light	t_light;
typedef	struct s_rgb	t_color;
typedef struct s_sphere	t_sphere;

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
};

typedef struct s_ray
{
	t_point3	org;
	t_vec3		dir;
};

// scene
typedef struct s_cam
{
	t_point3	org;
	t_vec3		dir;
	double		fov;
};

typedef struct s_rgb
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
};

typedef struct s_light
{
	t_point3	org;
	double		ratio;
	t_color		color;
};

typedef struct s_sphere
{
	t_point3	center;
	double		radius;
	t_color		color;
};

typedef struct s_plane
{

};

typedef struct s_ambient
{

};





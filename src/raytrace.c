/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrigny <yrigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 15:38:54 by yrigny            #+#    #+#             */
/*   Updated: 2024/08/26 16:27:49 by yrigny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

unsigned int	calculate_pixel(int x, int y, t_scene scene)
{
	t_point3	pixel;
	t_ray		ray;
	t_color		color;

	pixel = find_pixel_on_viewport(x, y, scene.v);
	ray = init_ray(scene.c, pixel);
	cast_ray(&ray, scene);
	color = ray_color(ray, scene);
	return ((color.r << 16) + (color.g << 8) + color.b);
}

t_point3	find_pixel_on_viewport(int x, int y, t_viewport v)
{
	t_vec3		vec_delta;
	t_point3	this_pixel;

	vec_delta = vector_add(vector_scale(v.pixel_delta_u, x), vector_scale(v.pixel_delta_v, y));
	this_pixel = vector_add(v.pixel00, vec_delta);
	return (this_pixel);
}

t_ray	init_ray(t_cam c, t_point3 pixel)
{
	t_ray	ray;

	ray.org = c.org;
	ray.dir = vector_subtract(pixel, c.org);
	ray.hit_object = false;
	ray.object = NULL;
	return (ray);
}

void	cast_ray(t_ray *ray, t_scene scene)
{
	intersect_sphere(ray, scene.c, scene.sp);
}

void	intersect_sphere(t_ray *ray, t_cam cam, t_sphere s)
{
	double	a;
	double	b;
	double	c;
	double	first_root;

	a = dot_product(ray->dir, ray->dir);
	b = -2 * dot_product(ray->dir, vector_subtract(s.center, ray->org));
	c = dot_product(vector_subtract(s.center, ray->org), vector_subtract(s.center, ray->org)) - s.radius * s.radius;
	if (b * b - 4 * a * c >= 0)
	{
		first_root = (-b - sqrt(b * b - 4 * a * c)) / (2 * a);
		if (first_root > 1)
		{
			ray->hit_object = true;
			ray->object = &s;
			ray->intersect = vector_add(cam.org, vector_scale(ray->dir, first_root));
		}
	}
}

t_color	ray_color(t_ray ray, t_scene scene)
{
	t_sphere	*s;
	t_color		ambiant;

	s = NULL;
	ambiant = color_scaler(scene.a.color, scene.a.ratio);
	if (ray.hit_object)
	{
		s = ray.object;
		return (s->color);
	}
	return (ambiant);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrigny <yrigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 15:38:54 by yrigny            #+#    #+#             */
/*   Updated: 2024/08/27 14:03:26 by yrigny           ###   ########.fr       */
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
	cast_ray(&ray, &scene);
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

void	cast_ray(t_ray *ray, t_scene *scene)
{
	intersect_sphere(ray, scene->c, &scene->sp);
}

void	intersect_sphere(t_ray *ray, t_cam cam, t_sphere *sp)
{
	double	a;
	double	b;
	double	c;
	double	first_root;

	a = dot_product(ray->dir, ray->dir);
	b = -2 * dot_product(ray->dir, vector_subtract(sp->center, ray->org));
	c = dot_product(vector_subtract(sp->center, ray->org), vector_subtract(sp->center, ray->org)) - sp->radius * sp->radius;
	if (b * b - 4 * a * c >= 0)
	{
		first_root = (-b - sqrt(b * b - 4 * a * c)) / (2 * a);
		if (first_root > 1)
		{
			ray->hit_object = true;
			ray->object = sp;
			ray->intersect = vector_add(cam.org, vector_scale(ray->dir, first_root));
		}
	}
}

t_color	ray_color(t_ray ray, t_scene scene)
{
	t_sphere	*sp;
	t_color		ambient;
	t_color		obj_ref;
	t_color		res;

	sp = NULL;
	ambient = color_scale(scene.a.color, scene.a.ratio);
	if (ray.hit_object)
	{
		sp = ray.object;
		obj_ref = color_scale(sp->color, light_weight(&ray, sp, scene.l));
		res = color_add(obj_ref, ambient);
		return (res);
	}
	return (ambient);
}

double	light_weight(t_ray *ray, t_sphere *sp, t_light l)
{
	t_vec3	surface_normal;
	double	light_weight;

	surface_normal = vector_normalize(vector_subtract(ray->intersect, sp->center));
	light_weight = dot_product(vector_normalize(vector_subtract(l.org, ray->intersect)), surface_normal);
	return (light_weight < 0 ? 0 : light_weight);
}
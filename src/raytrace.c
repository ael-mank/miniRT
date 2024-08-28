/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrigny <yrigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 15:38:54 by yrigny            #+#    #+#             */
/*   Updated: 2024/08/28 14:36:24 by yrigny           ###   ########.fr       */
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
	ray.object_type = DEFAULT;
	ray.object = NULL;
	return (ray);
}

void	cast_ray(t_ray *ray, t_scene *scene)
{
	intersect_sphere(ray, scene->c, &scene->sp);
	intersect_plane(ray, scene->c, &scene->pl);
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
			ray->object_type = SPHERE;
			ray->object = sp;
			ray->hit_distance = first_root;
			ray->intersect = vector_add(cam.org, vector_scale(ray->dir, first_root));
		}
	}
}

void	intersect_plane(t_ray *ray, t_cam cam, t_plane *pl)
{
	t_vec3		cam_p0;
	double		cam_p0_dot_normal;
	double		ray_dot_normal;
	double		root;

	cam_p0 = vector_subtract(pl->point_instance, cam.org);
	cam_p0_dot_normal = dot_product(cam_p0, pl->normal);
	ray_dot_normal = dot_product(ray->dir, pl->normal);
	if (ray_dot_normal != 0)
	{
		root = cam_p0_dot_normal / ray_dot_normal;
		if (root > 1 && (!ray->hit_object || (ray->hit_object && root < ray->hit_distance)))
		{
			ray->hit_object = true;
			ray->object_type = PLANE;
			ray->object = pl;
			ray->hit_distance = root;
			ray->intersect = vector_add(cam.org, vector_scale(ray->dir, root));
		}
	}
}

t_color	ray_color(t_ray ray, t_scene scene)
{
	t_color		ambient;
	t_color		from_obj;
	t_color		res;

	ambient = color_scale(scene.a.color, scene.a.ratio);
	if (ray.hit_object)
	{
		from_obj = weighted_obj_color(&ray, ray.object, scene.l);
		res = color_add(from_obj, ambient);
		return (res);
	}
	return (ambient);
}

t_color	weighted_obj_color(t_ray *ray, void *obj, t_light l)
{
	t_color	obj_color;
	t_color	weighted;

	if (ray->object_type == SPHERE)
		obj_color = ((t_sphere *)obj)->color;
	if (ray->object_type == PLANE)
		obj_color = ((t_plane *)obj)->color;
	weighted = color_scale(obj_color, light_weight(ray, obj, l));
	return (weighted);
}

double	light_weight(t_ray *ray, void *obj, t_light l)
{
	t_vec3	surface_normal;
	double	light_weight;

	if (ray->object_type == SPHERE)
		surface_normal = vector_normalize(vector_subtract(ray->intersect, ((t_sphere *)obj)->center));
	if (ray->object_type == PLANE)
		surface_normal = vector_normalize(((t_plane *)obj)->normal);
 	light_weight = dot_product(vector_normalize(vector_subtract(l.org, ray->intersect)), surface_normal);
	if (light_weight < 0)
		return (0);
	return (light_weight);
}
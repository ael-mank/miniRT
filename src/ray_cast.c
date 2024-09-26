/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrigny <yrigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 15:38:54 by yrigny            #+#    #+#             */
/*   Updated: 2024/09/26 12:43:34 by yrigny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_point3	find_pixel_on_viewport(int x, int y, t_viewport v)
{
	t_vec3		vec_delta;
	t_point3	this_pixel;

	vec_delta = vector_add(vector_scale(v.pixel_delta_u, x),
			vector_scale(v.pixel_delta_v, y));
	this_pixel = vector_add(v.pixel00, vec_delta);
	return (this_pixel);
}

t_ray	init_ray(t_cam *c, t_point3 pixel)
{
	t_ray	ray;

	ray.org = pixel;
	ray.dir = vector_subtract(pixel, c->org);
	ray.dir = vector_normalize(ray.dir);
	ray.hit_status = NO_HIT;
	ray.object_type = DEFAULT;
	ray.object = NULL;
	return (ray);
}

void	cast_ray(t_ray *ray, t_scene *scene)
{
	t_obj	*node;

	node = scene->objs;
	while (node)
	{
		if (node->type == SPHERE)
			intersect_sphere(ray, node->obj);
		else if (node->type == PLANE)
			intersect_plane(ray, node->obj);
		else if (node->type == CYLINDER)
		{
			intersect_cylinder_front(ray, node->obj);
			intersect_cylinder_back(ray, node->obj);
		}
		if (ray->hit_status == FALSE_HIT)
			break ;
		node = node->next;
	}
	if (ray->hit_status == TRUE_HIT)
		check_shadow(ray, scene);
}

void	check_shadow(t_ray *ray, t_scene *scene)
{
	t_obj	*node;
	t_ray	shadow_ray;

	shadow_ray.org = ray->intersect;
	shadow_ray.dir = vector_subtract(scene->l->org, ray->intersect);
	shadow_ray.hit_status = NO_HIT;
	shadow_ray.object = NULL;
	node = scene->objs;
	while (node)
	{
		if (node->obj != ray->object && node->type == SPHERE)
			intersect_sphere(&shadow_ray, node->obj);
		else if (node->obj != ray->object && node->type == PLANE)
			intersect_plane(&shadow_ray, node->obj);
		else if (node->obj != ray->object && node->type == CYLINDER)
		{
			intersect_cylinder_front(&shadow_ray, node->obj);
			intersect_cylinder_back(&shadow_ray, node->obj);
		}
		if (shadow_ray.hit_status == TRUE_HIT && shadow_ray.hit_distance < 1)
			break ;
		node = node->next;
	}
	if (shadow_ray.hit_status == TRUE_HIT && shadow_ray.hit_distance < 1)
		ray->hit_status = SHADOWED;
}

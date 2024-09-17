/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrigny <yrigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 15:38:54 by yrigny            #+#    #+#             */
/*   Updated: 2024/09/17 22:21:46 by yrigny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

unsigned int	calculate_pixel(int x, int y, t_scene *scene)
{
	t_point3	pixel;
	t_ray		ray;
	t_color		color;

	pixel = find_pixel_on_viewport(x, y, scene->c->v);
	ray = init_ray(scene->c, pixel);
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

t_ray	init_ray(t_cam *c, t_point3 pixel)
{
	t_ray	ray;

	ray.org = c->org;
	ray.dir = vector_subtract(pixel, c->org);
	ray.hit_object = NO_HIT;
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
			intersect_sphere(ray, *(scene->c), node->obj);
		else if (node->type == PLANE)
			intersect_plane(ray, *(scene->c), node->obj);
		else if (node->type == CYLINDER)
		{
			intersect_cylinder_front(ray, *(scene->c), node->obj);
			intersect_cylinder_back(ray, *(scene->c), node->obj);
		}
		if (ray->hit_object == FALSE_HIT)
			break ;
		node = node->next;
	}
	// intersect_sphere(ray, *(scene->c), &scene->sp);
	// if (ray->hit_object == FALSE_HIT)
	// 	return ;
	// intersect_plane(ray, scene->c, &scene->pl);
	// if (ray->hit_object == FALSE_HIT)
	// 	return ;
	// intersect_cylinder_front(ray, scene->c, &scene->cy);
	// intersect_cylinder_back(ray, scene->c, &scene->cy);
}

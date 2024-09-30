/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrigny <yrigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 19:09:41 by yrigny            #+#    #+#             */
/*   Updated: 2024/09/30 16:55:32 by yrigny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
/*
t_color	ray_color(t_ray *ray, t_scene *scene)
{
	t_color	ambient;
	t_color	from_obj;
	t_color	res;
	double	diffuse_ratio;

	ambient = color_scale(scene->a->color, scene->a->ratio);
	diffuse_ratio = light_weight(ray, ray->object, scene->l);
	from_obj = weighted_obj_color(ray, ray->object, diffuse_ratio);
	if (ray->hit_status != NO_HIT)
		res = color_add(from_obj, ambient);
	else
		res = ambient;
	return (res);
}*/

t_color	ray_color(t_ray *ray, t_scene *scene)
{
	double	light_impact;
	t_color	light;
	t_color	obj_with_ambient;
	t_color	res;

	if (ray->hit_status == NO_HIT)
		res = color_scale(scene->a->color, scene->a->ratio);
	else
	{
		light_impact = light_weight(ray, ray->object, scene->l);
		light = color_scale(scene->l->color, scene->l->ratio * light_impact);
		obj_with_ambient = ambient_on_obj(ray, ray->object, scene->a);
		res = color_add(light, obj_with_ambient);
	}
	return (res);
}

t_color	ambient_on_obj(t_ray *ray, void *obj, t_ambient *a)
{
	t_color	ambient;
	t_color	obj_color;
	t_color	res;

	ambient = color_scale(a->color, a->ratio);
	if (ray->object_type == SPHERE)
		obj_color = ((t_sphere *)obj)->color;
	if (ray->object_type == PLANE)
		obj_color = ((t_plane *)obj)->color;
	if (ray->object_type == CYLINDER_E || ray->object_type == CYLINDER_I)
		obj_color = ((t_cylinder *)obj)->color;
	res = color_multiply(obj_color, ambient);
	return (res);
}

t_color	weighted_obj_color(t_ray *ray, void *obj, double diffuse_ratio)
{
	t_color	obj_color;
	t_color	weighted;

	if (ray->object_type == SPHERE)
		obj_color = ((t_sphere *)obj)->color;
	if (ray->object_type == PLANE)
		obj_color = ((t_plane *)obj)->color;
	if (ray->object_type == CYLINDER_E || ray->object_type == CYLINDER_I)
		obj_color = ((t_cylinder *)obj)->color;
	weighted = color_scale(obj_color, diffuse_ratio);
	return (weighted);
}

double	light_weight(t_ray *ray, void *obj, t_light *l)
{
	t_vec3	surface_normal;
	double	light_weight;

	surface_normal = get_normal(ray, obj);
	if (ray->hit_status == FALSE_HIT && (vector_length
			(vector_subtract(((t_sphere *)obj)->center, l->org))
			> ((t_sphere *)obj)->radius))
		light_weight = 0;
	else if (ray->hit_status == SHADOWED)
		light_weight = 0;
	else
		light_weight = dot_product(vector_normalize(vector_subtract
					(l->org, ray->intersect)), surface_normal) * l->ratio;
	if (light_weight < 0)
		return (0);
	return (light_weight);
}

t_vec3	get_normal(t_ray *ray, void *obj)
{
	t_vec3	normal;
	t_vec3	temp[2];

	if (ray->object_type == SPHERE)
		normal = vector_normalize(vector_subtract(ray->intersect,
					((t_sphere *)obj)->center));
	if (ray->hit_status == FALSE_HIT)
		normal = vector_scale(normal, -1);
	if (ray->object_type == PLANE)
		normal = vector_normalize(((t_plane *)obj)->normal);
	if (ray->object_type == CYLINDER_E || ray->object_type == CYLINDER_I)
	{
		temp[0] = vector_subtract(ray->intersect, ((t_cylinder *)obj)->center);
		temp[1] = vector_scale(((t_cylinder *)obj)->axis, dot_product(temp[0],
					((t_cylinder *)obj)->axis));
		normal = vector_normalize(vector_subtract(temp[0], temp[1]));
		if (ray->object_type == CYLINDER_I)
			normal = vector_scale(normal, -1);
	}
	return (normal);
}

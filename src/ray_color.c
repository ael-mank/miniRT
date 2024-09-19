/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrigny <yrigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 19:09:41 by yrigny            #+#    #+#             */
/*   Updated: 2024/09/19 15:39:10 by yrigny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	ray_color(t_ray *ray, t_scene *scene)
{
	t_color		ambient;
	t_color		from_obj;
	t_color		res;

	ambient = color_scale(scene->a->color, scene->a->ratio);
	if (ray->hit_object == TRUE_HIT)
	{
		from_obj = weighted_obj_color(ray, ray->object, scene->l);
		res = color_add(from_obj, ambient);
		return (res);
	}
	else if (ray->hit_object == FALSE_HIT && ray->object_type == SPHERE)
	{
		// printf("X");
		return (color(50, 50, 50));
	}
	else
	{
		// printf("X");
		return (ambient);
	}
}

// t_color norm(t_ray *ray, void *obj) {
// 	t_vec3	surface_normal;
// 	t_vec3	temp[2];
// 	t_color	clr;

// 	clr = color(0,0,0);
// if (ray->object_type == CYLINDER)
// 	{
// 		temp[0] = vector_subtract(ray->intersect, ((t_cylinder *)obj)->center);
// 		temp[1] = vector_scale(((t_cylinder *)obj)->axis, dot_product(temp[0], ((t_cylinder *)obj)->axis));
// 		surface_normal = vector_normalize(vector_add(temp[0], temp[1]));
// 	}
// 	clr.r = surface_normal.x * 255;
// 	clr.g = surface_normal.y * 255;
// 	clr.b = surface_normal.z * 255;
// 	return clr;
// }


t_color	weighted_obj_color(t_ray *ray, void *obj, t_light *l)
{
	t_color	obj_color;
	t_color	weighted;

	if (ray->object_type == SPHERE)
	{
		obj_color = ((t_sphere *)obj)->color;
		// printf("%d,%d,%d ", obj_color.r, obj_color.g, obj_color.b);
	}
	if (ray->object_type == PLANE)
		obj_color = ((t_plane *)obj)->color;
	if (ray->object_type == CYLINDER)
		obj_color = ((t_cylinder *)obj)->color;
	// return (norm(ray, obj));
	weighted = color_scale(obj_color, light_weight(ray, obj, l));
	// if (ray->object_type == SPHERE)
	// 	printf("%d,%d,%d ", weighted.r, weighted.g, weighted.b);
	return (weighted);
}

double	light_weight(t_ray *ray, void *obj, t_light *l)
{
	t_vec3	surface_normal;
	t_vec3	temp[2];
	double	light_weight;

	if (ray->object_type == SPHERE)
		surface_normal = vector_normalize(vector_subtract(ray->intersect, ((t_sphere *)obj)->center));
	if (ray->object_type == PLANE)
		surface_normal = vector_normalize(((t_plane *)obj)->normal);
	if (ray->object_type == CYLINDER)
	{
		temp[0] = vector_subtract(ray->intersect, ((t_cylinder *)obj)->center);
		temp[1] = vector_scale(((t_cylinder *)obj)->axis, dot_product(temp[0], ((t_cylinder *)obj)->axis));
		surface_normal = vector_normalize(vector_add(temp[0], temp[1]));
	}
 	light_weight = dot_product(vector_normalize(vector_subtract(l->org, ray->intersect)), surface_normal);
	if (light_weight < 0)
		return (0);
	return (light_weight);
}

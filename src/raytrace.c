/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrigny <yrigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 15:38:54 by yrigny            #+#    #+#             */
/*   Updated: 2024/09/09 17:27:05 by yrigny           ###   ########.fr       */
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
	ray.hit_object = NO_HIT;
	ray.object_type = DEFAULT;
	ray.object = NULL;
	return (ray);
}

void	cast_ray(t_ray *ray, t_scene *scene)
{
	intersect_sphere(ray, scene->c, &scene->sp);
	if (ray->hit_object == FALSE_HIT)
		return ;
	intersect_plane(ray, scene->c, &scene->pl);
	if (ray->hit_object == FALSE_HIT)
		return ;
	intersect_cylinder_front(ray, scene->c, &scene->cy);
	intersect_cylinder_back(ray, scene->c, &scene->cy);
}

void	solve_equation(t_root *res, double a, double b, double c)
{
	res->delta = b * b - 4 * a * c;
	if (res->delta < 0)
		res->hit = NO_HIT;
	else
	{
		res->root1 = (-b - sqrt(res->delta)) / (2 * a);
		res->root2 = (-b + sqrt(res->delta)) / (2 * a);
		if (res->root2 < 0.0)
			res->hit = NO_HIT;
		else if (res->root1 > 1.0)
			res->hit = TRUE_HIT;
		else
			res->hit = FALSE_HIT;
	}
}

void	intersect_sphere(t_ray *ray, t_cam cam, t_sphere *sp)
{
	double	a;
	double	b;
	double	c;
	t_root	res;

	a = dot_product(ray->dir, ray->dir);
	b = -2 * dot_product(ray->dir, vector_subtract(sp->center, ray->org));
	c = dot_product(vector_subtract(sp->center, ray->org), vector_subtract(sp->center, ray->org)) - pow(sp->radius, 2);
	solve_equation(&res, a, b, c);
	if (res.hit == TRUE_HIT)
	{
		ray->hit_object = TRUE_HIT;
		ray->object_type = SPHERE;
		ray->object = sp;
		ray->hit_distance = res.root1;
		ray->intersect = vector_add(cam.org, vector_scale(ray->dir, res.root1));
	}
	else if (res.hit == FALSE_HIT)
		ray->hit_object = FALSE_HIT;
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
			ray->hit_object = TRUE_HIT;
			ray->object_type = PLANE;
			ray->object = pl;
			ray->hit_distance = root;
			ray->intersect = vector_add(cam.org, vector_scale(ray->dir, root));
		}
		else if (root > 0 && root < 1)
			ray->hit_object = FALSE_HIT;
	}
}

void	intersect_cylinder_front(t_ray *ray, t_cam cam, t_cylinder *cy)
{
	double	a;
	double	b;
	double	c;
	t_vec3	temp[3];
	double	root;

	temp[0] = vector_subtract(cam.org, cy->center);
	temp[1] = cross_product(ray->dir, cy->axis);
	temp[2] = cross_product(temp[0], cy->axis);
	a = dot_product(temp[1], temp[1]);
	b = 2 * dot_product(temp[1], temp[2]);
	c = dot_product(temp[2], temp[2]) - pow(cy->radius * vector_length(cy->axis), 2);
	if (b * b - 4 * a * c >= 0)
	{
		root = (-b - sqrt(b * b - 4 * a * c)) / (2 * a);
		if (root > 1 && (!ray->hit_object || (ray->hit_object && root < ray->hit_distance)) && in_cylinder_limit(root, cam, ray, cy))
		{
			ray->hit_object = TRUE_HIT;
			ray->object_type = CYLINDER;
			ray->object = cy;
			ray->hit_distance = root;
			ray->intersect = vector_add(cam.org, vector_scale(ray->dir, root));
		}
	}
}

void	intersect_cylinder_back(t_ray *ray, t_cam cam, t_cylinder *cy)
{
	double	a;
	double	b;
	double	c;
	t_vec3	temp[3];
	double	root;

	temp[0] = vector_subtract(cam.org, cy->center);
	temp[1] = cross_product(ray->dir, cy->axis);
	temp[2] = cross_product(temp[0], cy->axis);
	a = dot_product(temp[1], temp[1]);
	b = 2 * dot_product(temp[1], temp[2]);
	c = dot_product(temp[2], temp[2]) - pow(cy->radius * vector_length(cy->axis), 2);
	if (b * b - 4 * a * c >= 0)
	{
		root = (-b + sqrt(b * b - 4 * a * c)) / (2 * a);
		if (root > 1 && (!ray->hit_object || (ray->hit_object && root < ray->hit_distance)) && in_cylinder_limit(root, cam, ray, cy))
		{
			ray->hit_object = TRUE_HIT;
			ray->object_type = CYLINDER;
			ray->object = cy;
			ray->hit_distance = root;
			ray->intersect = vector_add(cam.org, vector_scale(ray->dir, root));
		}
	}
}

bool	in_cylinder_limit(double root, t_cam c, t_ray *ray, t_cylinder *cy)
{
	t_point3	intersect_p;
	t_vec3		p_center;

	intersect_p = vector_add(c.org, vector_scale(ray->dir, root));
	p_center = vector_subtract(cy->center, intersect_p);
	if (pow(dot_product(p_center, cy->axis), 2) <= pow(cy->height / 2.0, 2))
		return (true);
	return (false);
}

t_color	ray_color(t_ray ray, t_scene scene)
{
	t_color		ambient;
	t_color		from_obj;
	t_color		res;

	ambient = color_scale(scene.a.color, scene.a.ratio);
	if (ray.hit_object == TRUE_HIT)
	{
		from_obj = weighted_obj_color(&ray, ray.object, scene.l);
		res = color_add(from_obj, ambient);
		return (res);
	}
	else if (ray.hit_object == FALSE_HIT)
		return (color(0, 0, 0));
	else // no hit
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
	if (ray->object_type == CYLINDER)
		obj_color = ((t_cylinder *)obj)->color;
	weighted = color_scale(obj_color, light_weight(ray, obj, l));
	return (weighted);
}

double	light_weight(t_ray *ray, void *obj, t_light l)
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
 	light_weight = dot_product(vector_normalize(vector_subtract(l.org, ray->intersect)), surface_normal);
	if (light_weight < 0)
		return (0);
	return (light_weight);
}
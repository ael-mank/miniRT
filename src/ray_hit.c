/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_hit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrigny <yrigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 19:12:32 by yrigny            #+#    #+#             */
/*   Updated: 2024/09/19 14:36:25 by yrigny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	solve_equation(t_root *res, double a, double b, double c)
{
	res->delta = b * b - 4 * a * c;
	if (res->delta < 0)
		res->hit = NO_HIT;
	else
	{
		res->root1 = (-b - sqrt(res->delta)) / (2 * a);
		res->root2 = (-b + sqrt(res->delta)) / (2 * a);
		if (res->root2 < 1.0)
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
	{
		ray->hit_object = FALSE_HIT;
		ray->object_type = SPHERE;
	}
}

void	intersect_plane(t_ray *ray, t_cam cam, t_plane *pl)
{
	t_vec3		cam_p0;
	double		cam_p0_dot_normal;
	double		ray_dot_normal;
	double		root;

	cam_p0 = vector_subtract(pl->point, cam.org);
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

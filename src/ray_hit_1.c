/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_hit_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrigny <yrigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 19:12:32 by yrigny            #+#    #+#             */
/*   Updated: 2024/09/26 18:22:08 by yrigny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	sphere_equation(t_root *res, double a, double b, double c)
{
	res->delta = b * b - 4 * a * c;
	if (res->delta < 0)
		res->hit = NO_HIT;
	else
	{
		res->root1 = (-b - sqrt(res->delta)) / (2 * a);
		res->root2 = (-b + sqrt(res->delta)) / (2 * a);
		if (res->root1 > 0)
		{
			res->hit = TRUE_HIT;
			res->root = res->root1;
		}
		else if (res->root1 < 0 && res->root2 > 0)
		{
			res->hit = FALSE_HIT;
			res->root = res->root2;
		}
		else
			res->hit = NO_HIT;
	}
}

void	intersect_sphere(t_ray *ray, t_sphere *sp)
{
	double	a;
	double	b;
	double	c;
	t_root	res;

	a = dot_product(ray->dir, ray->dir);
	b = -2 * dot_product(ray->dir, vector_subtract(sp->center, ray->org));
	c = dot_product(vector_subtract(sp->center, ray->org),
			vector_subtract(sp->center, ray->org)) - pow(sp->radius, 2);
	sphere_equation(&res, a, b, c);
	if (res.hit != NO_HIT && (!ray->hit_status || (ray->hit_status
				&& res.root < ray->hit_distance)))
	{
		ray->hit_status = res.hit;
		ray->object_type = SPHERE;
		ray->object = sp;
		ray->hit_distance = res.root;
		ray->intersect = vector_add(ray->org, vector_scale(ray->dir,
					res.root));
	}
}

void	intersect_plane(t_ray *ray, t_plane *pl)
{
	t_vec3	ray_to_p0;
	double	ray_p0_dot_normal;
	double	ray_dot_normal;
	double	root;

	ray_to_p0 = vector_subtract(pl->point, ray->org);
	ray_p0_dot_normal = dot_product(ray_to_p0, pl->normal);
	ray_dot_normal = dot_product(ray->dir, pl->normal);
	if (ray_dot_normal != 0)
	{
		root = ray_p0_dot_normal / ray_dot_normal;
		if (root > 0 && (!ray->hit_status || (ray->hit_status
					&& root < ray->hit_distance)))
		{
			ray->hit_status = TRUE_HIT;
			ray->object_type = PLANE;
			ray->object = pl;
			ray->hit_distance = root;
			ray->intersect = vector_add(ray->org, vector_scale(ray->dir, root));
		}
	}
}

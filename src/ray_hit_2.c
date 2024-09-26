/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_hit_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrigny <yrigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 20:50:04 by yrigny            #+#    #+#             */
/*   Updated: 2024/09/26 12:31:50 by yrigny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	cy_quadratic_coefficient(t_ray *ray, t_cylinder *cy)
{
	t_vec3	coef;
	t_vec3	temp[3];

	temp[0] = vector_subtract(ray->org, cy->center);
	temp[1] = cross_product(ray->dir, cy->axis);
	temp[2] = cross_product(temp[0], cy->axis);
	coef.x = dot_product(temp[1], temp[1]);
	coef.y = 2 * dot_product(temp[1], temp[2]);
	coef.z = dot_product(temp[2], temp[2]) - pow(cy->radius
			* vector_length(cy->axis), 2);
	return (coef);
}

void	intersect_cylinder_front(t_ray *ray, t_cylinder *cy)
{
	double	a;
	double	b;
	double	c;
	t_vec3	coef;
	double	root;

	coef = cy_quadratic_coefficient(ray, cy);
	a = coef.x;
	b = coef.y;
	c = coef.z;
	if (b * b - 4 * a * c >= 0)
	{
		root = (-b - sqrt(b * b - 4 * a * c)) / (2 * a);
		if (root > 0 && (!ray->hit_status || (ray->hit_status
					&& root < ray->hit_distance))
			&& in_cylinder_limit(root, ray, cy))
		{
			ray->hit_status = TRUE_HIT;
			ray->object_type = CYLINDER_E;
			ray->object = cy;
			ray->hit_distance = root;
			ray->intersect = vector_add(ray->org, vector_scale(ray->dir, root));
		}
	}
}

void	intersect_cylinder_back(t_ray *ray, t_cylinder *cy)
{
	double	a;
	double	b;
	double	c;
	t_vec3	coef;
	double	root;

	coef = cy_quadratic_coefficient(ray, cy);
	a = coef.x;
	b = coef.y;
	c = coef.z;
	if (b * b - 4 * a * c >= 0)
	{
		root = (-b + sqrt(b * b - 4 * a * c)) / (2 * a);
		if (root > 0 && (!ray->hit_status || (ray->hit_status
					&& root < ray->hit_distance))
			&& in_cylinder_limit(root, ray, cy))
		{
			ray->hit_status = TRUE_HIT;
			ray->object_type = CYLINDER_I;
			ray->object = cy;
			ray->hit_distance = root;
			ray->intersect = vector_add(ray->org, vector_scale(ray->dir, root));
		}
	}
}

bool	in_cylinder_limit(double root, t_ray *ray, t_cylinder *cy)
{
	t_point3	intersect_p;
	t_vec3		p_center;

	intersect_p = vector_add(ray->org, vector_scale(ray->dir, root));
	p_center = vector_subtract(cy->center, intersect_p);
	if (pow(dot_product(p_center, cy->axis), 2) <= pow(cy->height / 2.0, 2))
		return (true);
	return (false);
}

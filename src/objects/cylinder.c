/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 07:58:29 by ael-mank          #+#    #+#             */
/*   Updated: 2024/09/28 18:14:20 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	get_cylinder_uv(t_vec3 p, t_cylinder cylinder, double *u, double *v)
{
	double	theta;
	t_vec3	relative_p;

	relative_p = vector_subtract(p, cylinder.center);
	theta = atan2(relative_p.z, relative_p.x);
	*u = (theta + M_PI) / (2 * M_PI);
	*v = dot(relative_p, cylinder.axis) / cylinder.height + 0.5;
}

static inline double	calculate_discriminant(t_vec3 d, t_vec3 oc_proj,
		double radius, double *params)
{
	double	c;

	params[0] = vector_length_squared(d);
	params[1] = dot(d, oc_proj);
	c = vector_length_squared(oc_proj) - radius * radius;
	return (params[1] * params[1] - params[0] * c);
}

static inline int	find_roots(double discriminant, double *params,
		t_interval ray_t, double *roots)
{
	double	sqrtd;

	sqrtd = sqrt(discriminant);
	roots[0] = (-params[1] - sqrtd) / params[0];
	roots[1] = (-params[1] + sqrtd) / params[0];
	return (contains(ray_t, roots[0]) || contains(ray_t, roots[1]));
}

static inline int	check_hit_point_and_height(t_ray r, t_cylinder cylinder,
		double root, t_hitrecord *rec)
{
	t_vec3	hit_point;
	double	hit_height;
	t_vec3	outward_normal;

	hit_point = ray_at(&r, root);
	hit_height = dot(vector_subtract(hit_point, cylinder.center),
			cylinder.axis);
	if (hit_height < -cylinder.height / 2 || hit_height > cylinder.height / 2)
	{
		return (0);
	}
	rec->t = root;
	rec->p = hit_point;
	outward_normal = vector_normalize(vector_subtract(vector_subtract(rec->p,
					cylinder.center), vector_scale(cylinder.axis, hit_height)));
	set_face_normal_cy(rec, &r, outward_normal);
	get_cylinder_uv(rec->p, cylinder, &rec->u, &rec->v);
	rec->mat = cylinder.mat;
	return (1);
}

double	hit_cylinder(t_ray r, t_cylinder cylinder,
		t_interval ray_t, t_hitrecord *rec)
{
	t_vec3	oc;
	t_vec3	d;
	t_vec3	oc_proj;
	double	params[5];

	oc = vector_subtract(r.org, cylinder.center);
	d = vector_subtract(r.dir, vector_scale(cylinder.axis, dot(r.dir,
					cylinder.axis)));
	oc_proj = vector_subtract(oc, vector_scale(cylinder.axis, dot(oc,
					cylinder.axis)));
	params[2] = calculate_discriminant(d, oc_proj, cylinder.radius, params);
	if (params[2] < 0)
		return (0);
	if (!find_roots(params[2], params, ray_t, &params[3]))
		return (0);
	if (contains(ray_t, params[3]) && check_hit_point_and_height(r, cylinder,
			params[3], rec))
		return (1);
	if (contains(ray_t, params[4]) && check_hit_point_and_height(r, cylinder,
			params[4], rec))
		return (1);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 07:58:29 by ael-mank          #+#    #+#             */
/*   Updated: 2024/09/17 11:21:32 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	set_face_normal_cy(t_hitrecord *rec, t_ray *r, t_vec3 outward_normal)
{
	rec->front_face = dot(r->dir, outward_normal) < 0;
	rec->normal = rec->front_face ? outward_normal : vector_scale(outward_normal,
			-1);
}

void	get_cylinder_uv(t_vec3 p, double *u, double *v)
{
	double	theta;

	theta = atan2(p.z, p.x);
	*u = (theta + M_PI) / (2 * M_PI);
	*v = p.y; // Assuming the cylinder's axis is aligned with the y-axis
}

static inline double	hit_cylinder(t_ray r, t_cylinder cylinder,
		t_interval ray_t, t_hitrecord *rec)
{
	t_vec3	oc;
	double	a;
	double	half_b;
	double	c;
	double	discriminant;
	double	sqrtd;
	double	root;
	t_vec3	d;
	t_vec3	oc_proj;
	t_vec3	hit_point;
	double	hit_height;
	t_vec3	outward_normal;

	d = vector_subtract(r.dir, vector_scale(cylinder.axis, dot(r.dir,
					cylinder.axis)));
	oc = vector_subtract(r.org, cylinder.center);
	oc_proj = vector_subtract(oc, vector_scale(cylinder.axis, dot(oc,
					cylinder.axis)));
	a = vector_length_squared(d);
	half_b = dot(d, oc_proj);
	c = vector_length_squared(oc_proj) - cylinder.radius * cylinder.radius;
	discriminant = half_b * half_b - a * c;
	if (discriminant < 0)
		return (0);
	sqrtd = sqrt(discriminant);
	root = (-half_b - sqrtd) / a;
	if (!contains(ray_t, root))
	{
		root = (-half_b + sqrtd) / a;
		if (!contains(ray_t, root))
			return (0);
	}
	hit_point = ray_at(&r, root);
	hit_height = dot(vector_subtract(hit_point, cylinder.center),
			cylinder.axis);
	if (hit_height < -cylinder.height / 2 || hit_height > cylinder.height / 2)
	{
		root = (-half_b + sqrtd) / a;
		if (!contains(ray_t, root))
			return (0);
		hit_point = ray_at(&r, root);
		hit_height = dot(vector_subtract(hit_point, cylinder.center),
				cylinder.axis);
		if (hit_height < -cylinder.height / 2 || hit_height > cylinder.height
			/ 2)
			return (0);
	}
	rec->t = root;
	rec->p = hit_point;
	outward_normal = vector_normalize(vector_subtract(vector_subtract(rec->p,
					cylinder.center), vector_scale(cylinder.axis, hit_height)));
	set_face_normal_cy(rec, &r, outward_normal);
	get_cylinder_uv(outward_normal, &rec->u, &rec->v);
	rec->mat = cylinder.mat;
	return (1);
}

double	hit_cylinder_wrapper(t_ray r, void *object, t_interval ray_t,
		t_hitrecord *rec)
{
	return (hit_cylinder(r, *(t_cylinder *)object, ray_t, rec));
}
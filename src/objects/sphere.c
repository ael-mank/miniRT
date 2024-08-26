/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 15:46:59 by ael-mank          #+#    #+#             */
/*   Updated: 2024/08/26 14:25:37 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	set_face_normal(t_hitrecord *rec, t_ray *r, t_sphere sphere,
		double root)
{
	rec->t = root;
	rec->p = ray_at(r, rec->t);
	rec->normal = vector_normalize(vector_subtract(rec->p, sphere.center));
	rec->front_face = dot(r->dir, rec->normal) < 0;
	if (!rec->front_face)
	{
		rec->normal = vector_scale(rec->normal, -1);
	}
}

void	get_sphere_uv(t_vec3 p, double *u, double *v)
{
	double	theta;
	double	phi;

	theta = acos(-p.y);
	phi = atan2(-p.z, p.x) + M_PI;
	*u = phi / (2 * M_PI);
	*v = theta / M_PI;
}

static inline double	hit_sphere(t_ray r, t_sphere sphere, t_interval ray_t, t_hitrecord *rec)
{
	t_vec3	oc;
	double	a;
	double	h;
	double	c;
	double	sqrtd;
	double	root;

	oc = vector_subtract(sphere.center, r.org);
	a = vector_length_squared(r.dir);
	h = dot(r.dir, oc);
	c = vector_length_squared(oc) - sphere.radius * sphere.radius;
	if (h * h - a * c < 0)
		return (0);
	sqrtd = sqrt(h * h - a * c);
	root = (h - sqrtd) / a;
	if (!surrond(ray_t, (t_interval){root, root}))
	{
		root = (h + sqrtd) / a;
		if (!surrond(ray_t, (t_interval){root, root}))
			return (0);
	}
	set_face_normal(rec, &r, sphere, root);
	get_sphere_uv(rec->normal, &rec->u, &rec->v);
	rec->mat = sphere.mat;
	return (1);
}

double	hit_sphere_wrapper(t_ray r, void *object, t_interval ray_t,
		t_hitrecord *rec)
{
	return (hit_sphere(r, *(t_sphere *)object, ray_t, rec));
}	
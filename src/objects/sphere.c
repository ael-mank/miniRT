/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 15:46:59 by ael-mank          #+#    #+#             */
/*   Updated: 2024/08/22 11:23:50 by ael-mank         ###   ########.fr       */
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

double	hit_sphere(t_ray r, t_sphere sphere, t_interval ray_t, t_hitrecord *rec)
{
	t_vec3	oc;
	double	a;
	double	h;
	double	c;
	double	discriminant;
	double	sqrtd;
	double	root;

	oc = vector_subtract(sphere.center, r.org);
	a = vector_length_squared(r.dir);
	h = dot(r.dir, oc);
	c = vector_length_squared(oc) - sphere.radius * sphere.radius;
	discriminant = h * h - a * c;
	if (discriminant < 0)
		return (0);
	sqrtd = sqrt(discriminant);
	root = (h - sqrtd) / a;
	if (!surrond(ray_t, (t_interval){root, root}))
	{
		root = (h + sqrtd) / a;
		if (!surrond(ray_t, (t_interval){root, root}))
			return (0);
	}
	set_face_normal(rec, &r, sphere, root);
	rec->mat = sphere.mat;
	rec->mat->albedo = sphere.mat->albedo;
	t_vec3 intersection_point = ray_at(&r, root);

    // Calculate texture coordinates (u, v)
    double theta = acos(-intersection_point.y / sphere.radius);
    double phi = atan2(-intersection_point.z, intersection_point.x) + M_PI;
    rec->u = phi / (2 * M_PI);
    rec->v = theta / M_PI;
	return (1);
}

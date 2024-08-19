/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pyramid.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 16:15:25 by ael-mank          #+#    #+#             */
/*   Updated: 2024/08/19 10:59:49 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	set_face_normal_tri(t_hitrecord *rec, t_ray *r, t_vec3 v0, t_vec3 v1,
		t_vec3 v2, double root)
{
	rec->t = root;
	rec->p = ray_at(r, rec->t);
	rec->normal = vector_normalize(cross_product(vector_subtract(v1, v0),
				vector_subtract(v2, v0)));
	rec->front_face = dot(r->dir, rec->normal) < 0;
}

int	hit_triangle(t_ray *r, t_vec3 v0, t_vec3 v1, t_vec3 v2, t_interval ray_t,
		t_hitrecord *rec, t_material *mat)
{
	t_vec3	edge1;
	t_vec3	edge2;
	t_vec3	h;
	t_vec3	s;
	t_vec3	q;
	double	a;
	double	f;
	double	u;
	double	v;
	double	t;

	edge1 = vector_subtract(v1, v0);
	edge2 = vector_subtract(v2, v0);
	h = cross_product(r->dir, edge2);
	a = dot(edge1, h);
	if (a > -0.000001 && a < 0.000001)
		return (0);
	f = 1.0 / a;
	s = vector_subtract(r->org, v0);
	u = f * dot(s, h);
	if (u < 0.0 || u > 1.0)
		return (0);
	q = cross_product(s, edge1);
	v = f * dot(r->dir, q);
	if (v < 0.0 || u + v > 1.0)
		return (0);
	t = f * dot(edge2, q);
	if (t < ray_t.min || t > ray_t.max)
		return (0);
	rec->t = t;
	rec->p = ray_at(r, t);
	rec->normal = vector_normalize(cross_product(edge1, edge2));
	set_face_normal_tri(rec, r, v0, v1, v2, t);
	rec->mat = mat;
	return (1);
}

double	hit_pyramid(t_ray r, t_pyramid pyramid, t_interval ray_t,
		t_hitrecord *rec)
{
	int		hit_anything;
	double	closest_so_far;

	hit_anything = 0;
	closest_so_far = ray_t.max;
	for (int i = 0; i < 4; i++)
	{
		if (hit_triangle(&r, pyramid.vertices[i], pyramid.vertices[(i + 1) % 4],
				pyramid.apex, ray_t, rec, pyramid.mat))
		{
			hit_anything = 1;
			closest_so_far = rec->t;
			ray_t.max = closest_so_far;
		}
	}
	if (hit_triangle(&r, pyramid.vertices[0], pyramid.vertices[1],
			pyramid.vertices[2], ray_t, rec, pyramid.mat))
	{
		hit_anything = 1;
		closest_so_far = rec->t;
		ray_t.max = closest_so_far;
	}
	if (hit_triangle(&r, pyramid.vertices[0], pyramid.vertices[2],
			pyramid.vertices[3], ray_t, rec, pyramid.mat))
	{
		hit_anything = 1;
		closest_so_far = rec->t;
		ray_t.max = closest_so_far;
	}
	return (hit_anything);
}

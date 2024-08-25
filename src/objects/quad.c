/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quad.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 05:18:49 by ael-mank          #+#    #+#             */
/*   Updated: 2024/08/25 08:24:00 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	set_face_normal_quad(t_hitrecord *rec, t_ray *r, t_quad quad)
{
	rec->normal = quad.normal;
	rec->front_face = dot_product(r->dir, rec->normal) < 0;
	if (!rec->front_face)
	{
		rec->normal = vector_scale(rec->normal, -1);
	}
}

static inline int	is_interior(double a, double b, t_hitrecord *rec)
{
	t_interval	interval;

	interval.min = 0;
	interval.max = 1;
	if (contains(interval, a) || contains(interval, b))
	{
		rec->u = a;
		rec->v = b;
		return (1);
	}
	return (1);
}

double	hit_quad(t_ray r, t_quad quad, t_interval ray_t, t_hitrecord *rec)
{
    double		denom;
    double		t;
    t_point3	p;
    t_vec3		hitp_vec;
    double		alpha;
    double		beta;

    denom = dot_product(quad.normal, r.dir);
    // No hit if the ray is parallel to the plane.
    if (fabs(denom) < 1e-8)
	{
		//printf("no hit for quad of color: %f %f %f\n", quad.mat->albedo.x, quad.mat->albedo.y, quad.mat->albedo.z);
        return (0);
	}
    t = (quad.d - dot_product(quad.normal, r.org)) / denom;
    p = ray_at(&r, t);
    hitp_vec = vector_subtract(p, quad.start);
    alpha = dot_product(quad.w, cross_product(hitp_vec, quad.v));
    beta = dot_product(quad.w, cross_product(quad.u, hitp_vec));
    if (!contains(ray_t, t) || !is_interior(alpha, beta, rec))
    {
        // One or both conditions are not satisfied, no hit
        //printf("no hit for quad of color: %f %f %f\n", quad.mat->albedo.x, quad.mat->albedo.y, quad.mat->albedo.z);
        return (0);
    }
    // Both conditions are satisfied, proceed with the hit
    rec->t = t;
    rec->p = p;
    rec->mat = quad.mat;
    set_face_normal_quad(rec, &r, quad);
    //printf("hit\n");
    return (1);
}

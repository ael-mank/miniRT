/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quad.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 05:18:49 by ael-mank          #+#    #+#             */
/*   Updated: 2024/09/11 13:53:31 by ael-mank         ###   ########.fr       */
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
	t_interval	interval = (t_interval){0, 1};
	// Given the hit point in plane coordinates, return false if it is outside the
        // primitive, otherwise set the hit record UV coordinates and return true.
	if (!contains(interval, a) || !contains(interval, b))
	{
		return 0;
	}
	rec->u = a;
	rec->v = b;
	return 1;
}


static inline double	hit_quad(t_ray r, t_quad quad, t_interval ray_t, t_hitrecord *rec)
{
    double		denom;
    double		t;
    t_point3	p;
    t_vec3		hitp_vec;
    double		alpha;
    double		beta;

    denom = dot_product(quad.normal, r.dir);
    if (fabs(denom) < 1e-6)
    {
        return 0;
    }
    t = (quad.d - dot_product(quad.normal, r.org)) / denom;
    if (!contains(ray_t, t))
        return 0;
    p = ray_at(&r, t);
    hitp_vec = vector_subtract(p, quad.start);
    alpha = dot_product(quad.w, cross_product(quad.u, hitp_vec));
    beta = dot_product(quad.w, cross_product(hitp_vec, quad.v));
    
    // Debugging print statements
    printf("alpha: %f, beta: %f\n", alpha, beta);
    
    if (!is_interior(alpha, beta, rec))
        return 0;
    rec->t = t;
    rec->p = p;
    rec->mat = quad.mat;
    set_face_normal_quad(rec, &r, quad);
    return 1;
}

double	hit_quad_wrapper(t_ray r, void *object, t_interval ray_t,
		t_hitrecord *rec)
{
	return (hit_quad(r, *(t_quad *)object, ray_t, rec));
}
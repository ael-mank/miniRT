/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 05:18:49 by ael-mank          #+#    #+#             */
/*   Updated: 2024/09/16 11:50:52 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	set_face_normal_plane(t_hitrecord *rec, t_ray *r, t_plane plane)
{
    rec->normal = plane.normal;
    rec->front_face = dot_product(r->dir, rec->normal) < 0;
    if (!rec->front_face)
    {
        rec->normal = vector_scale(rec->normal, -1);
    }
}

static inline double	hit_plane(t_ray r, t_plane plane, t_interval ray_t, t_hitrecord *rec)
{
    double		denom;
    double		t;
    t_point3	p;

    denom = dot_product(plane.normal, r.dir);
    if (fabs(denom) < 1e-6)
    {
        return 0;
    }
  t = (dot_product(plane.normal, vector_subtract(plane.point, r.org))) / denom;
    if (!contains(ray_t, t))
        return 0;
    p = ray_at(&r, t);
    
    rec->t = t;
    rec->p = p;
    rec->mat = plane.mat;
    set_face_normal_plane(rec, &r, plane);
    return 1;
}

double	hit_plane_wrapper(t_ray r, void *object, t_interval ray_t, t_hitrecord *rec)
{
    return (hit_plane(r, *(t_plane *)object, ray_t, rec));
}
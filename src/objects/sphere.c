/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 15:46:59 by ael-mank          #+#    #+#             */
/*   Updated: 2024/09/11 19:47:42 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	set_face_normal(t_hitrecord *rec, t_ray *r, t_vec3 outward_normal)
{
    rec->front_face = dot(r->dir, outward_normal) < 0;
    rec->normal = rec->front_face ? outward_normal : vector_scale(outward_normal, -1);
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
    double	half_b;
    double	c;
    double	discriminant;
    double	sqrtd;
    double	root;

    oc = vector_subtract(r.org, sphere.center);
    a = vector_length_squared(r.dir);
    half_b = dot(r.dir, oc);
    c = vector_length_squared(oc) - sphere.radius * sphere.radius;
    discriminant = half_b * half_b - a * c;
    if (discriminant < 0)
        return (0);
    sqrtd = sqrt(discriminant);

    // Find the nearest root that lies in the acceptable range.
    root = (-half_b - sqrtd) / a;
    if (!contains(ray_t, root))
    {
        root = (-half_b + sqrtd) / a;
        if (!contains(ray_t, root))
            return (0);
    }

    rec->t = root;
    rec->p = ray_at(&r, root);
    t_vec3 outward_normal = vector_divide(vector_subtract(rec->p, sphere.center), sphere.radius);
    set_face_normal(rec, &r, outward_normal);
    get_sphere_uv(outward_normal, &rec->u, &rec->v);
    rec->mat = sphere.mat;
    return (1);
}

double	hit_sphere_wrapper(t_ray r, void *object, t_interval ray_t, t_hitrecord *rec)
{
    return (hit_sphere(r, *(t_sphere *)object, ray_t, rec));
}
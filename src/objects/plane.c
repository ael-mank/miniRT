/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 05:18:49 by ael-mank          #+#    #+#             */
/*   Updated: 2024/09/28 20:38:33 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	set_face_normal_plane(t_hitrecord *rec, t_ray *r, t_plane plane)
{
	rec->normal = plane.normal;
	rec->front_face = dot(r->dir, rec->normal) < 0;
	if (!rec->front_face)
	{
		rec->normal = vector_scale(rec->normal, -1);
	}
}

void	get_plane_uv(t_vec3 p, t_plane plane, double *u, double *v)
{
	t_vec3	u_axis;
	t_vec3	v_axis;
	t_vec3	relative_p;

	u_axis = cross_product(vec3(0, 1, 0), plane.normal);
	if (vector_length_squared(u_axis) < 1e-6)
		u_axis = cross_product(vec3(1, 0, 0), plane.normal);
	u_axis = vector_normalize(u_axis);
	v_axis = cross_product(plane.normal, u_axis);
	relative_p = vector_subtract(p, plane.point);
	*u = dot(relative_p, u_axis);
	*v = dot(relative_p, v_axis);
}

static inline double	hit_plane(t_ray r, t_plane plane, t_interval ray_t,
		t_hitrecord *rec)
{
	double		denom;
	double		t;
	t_point3	p;

	denom = dot(plane.normal, r.dir);
	if (fabs(denom) < 1e-6)
	{
		return (0);
	}
	t = (dot(plane.normal, vector_subtract(plane.point, r.org)))
		/ denom;
	if (!contains(ray_t, t))
		return (0);
	p = ray_at(&r, t);
	rec->t = t;
	rec->p = p;
	rec->mat = plane.mat;
	set_face_normal_plane(rec, &r, plane);
	get_plane_uv(p, plane, &rec->u, &rec->v);
	return (1);
}

double	hit_plane_wrapper(t_ray r, void *object, t_interval ray_t,
		t_hitrecord *rec)
{
	return (hit_plane(r, *(t_plane *)object, ray_t, rec));
}

void	free_plane(t_bvh *node)
{
	t_plane	*plane;

	plane = (t_plane *)node->object->object;
	if (plane->mat->img != NULL)
	{
		mlx_destroy_image(get_mlx_ptr(), plane->mat->img->image);
		free(plane->mat->img);
	}
	if (plane->mat != NULL)
		free(plane->mat);
	free(plane);
}

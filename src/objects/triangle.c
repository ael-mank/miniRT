/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 18:21:31 by ael-mank          #+#    #+#             */
/*   Updated: 2024/09/28 20:38:33 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static inline double	calculate_determinant(t_vec3 v0v1, t_vec3 pvec,
		double *params)
{
	params[0] = dot(v0v1, pvec);
	return (params[0]);
}

static inline int	find_uv(t_vec3 *vecs, double *params)
{
	params[4] = dot(vecs[4], vecs[3]) * params[1];
	if (params[4] < 0 || params[4] > 1)
		return (0);
	vecs[5] = cross_product(vecs[4], vecs[1]);
	params[5] = dot(vecs[0], vecs[5]) * params[1];
	if (params[5] < 0 || params[4] + params[5] > 1)
		return (0);
	params[6] = 1 - params[4] - params[5];
	return (1);
}

static inline int	is_interior_triangle(double *params, t_hitrecord *rec)
{
	if (params[4] < 0 || params[5] < 0 || params[6] < 0)
	{
		return (0);
	}
	rec->u = params[4];
	rec->v = params[5];
	return (1);
}

static inline int	check_denom_and_t(t_ray r, t_triangle triangle,
		double *params, t_interval ray_t)
{
	params[6] = dot(triangle.normal, r.dir);
	if (fabs(params[6]) < 1e-6)
		return (0);
	params[2] = (triangle.d - dot(triangle.normal, r.org)) / params[6];
	return (contains(ray_t, params[2]));
}

double	hit_triangle(t_ray r, t_triangle triangle,
		t_interval ray_t, t_hitrecord *rec)
{
	t_vec3	vecs[6];
	double	params[7];

	vecs[0] = vector_subtract(r.org, triangle.v0);
	vecs[1] = vector_subtract(triangle.v1, triangle.v0);
	vecs[2] = vector_subtract(triangle.v2, triangle.v0);
	vecs[3] = cross_product(r.dir, vecs[2]);
	params[0] = calculate_determinant(vecs[1], vecs[3], params);
	if (fabs(params[0]) < 1e-6)
		return (0);
	params[1] = 1 / params[0];
	if (!check_denom_and_t(r, triangle, params, ray_t))
		return (0);
	rec->t = params[2];
	rec->p = ray_at(&r, params[2]);
	vecs[4] = vector_subtract(r.org, triangle.v0);
	if (!find_uv(vecs, params))
		return (0);
	if (!is_interior_triangle(params, rec))
		return (0);
	rec->mat = triangle.mat;
	set_face_normal_triangle(rec, &r, triangle);
	return (1);
}

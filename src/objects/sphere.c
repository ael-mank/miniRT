/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 15:46:59 by ael-mank          #+#    #+#             */
/*   Updated: 2024/09/28 18:19:42 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static inline double	calculate_discriminant(t_vec3 oc, t_vec3 dir,
		double radius, double *params)
{
	params[0] = vector_length_squared(dir);
	params[1] = dot(dir, oc);
	params[2] = vector_length_squared(oc) - radius * radius;
	return (params[1] * params[1] - params[0] * params[2]);
}

static inline int	find_root(double discriminant, double *params,
		t_interval ray_t)
{
	double	sqrtd;

	sqrtd = sqrt(discriminant);
	params[4] = (-params[1] - sqrtd) / params[0];
	if (!contains(ray_t, params[4]))
	{
		params[4] = (-params[1] + sqrtd) / params[0];
		if (!contains(ray_t, params[4]))
		{
			return (0);
		}
	}
	return (1);
}

static inline double	hit_sphere(t_ray r, t_sphere sphere, t_interval ray_t,
		t_hitrecord *rec)
{
	t_vec3	oc;
	t_vec3	outward_normal;
	t_vec3	normal_color;
	double	params[5];

	oc = vector_subtract(r.org, sphere.center);
	params[3] = calculate_discriminant(oc, r.dir, sphere.radius, params);
	if (params[3] < 0)
		return (0);
	if (!find_root(params[3], params, ray_t))
		return (0);
	rec->t = params[4];
	rec->p = ray_at(&r, params[4]);
	outward_normal = vector_divide(vector_subtract(rec->p, sphere.center),
			sphere.radius);
	get_sphere_uv(outward_normal, &rec->u, &rec->v);
	if (sphere.mat->normal_map)
	{
		normal_color = get_texture_color(sphere.mat, rec);
		outward_normal = vector_add(outward_normal, normal_color);
		outward_normal = vector_normalize(outward_normal);
	}
	set_face_normal(rec, &r, outward_normal);
	rec->mat = sphere.mat;
	return (1);
}

double	hit_sphere_wrapper(t_ray r, void *object, t_interval ray_t,
		t_hitrecord *rec)
{
	return (hit_sphere(r, *(t_sphere *)object, ray_t, rec));
}

void	free_sphere(t_bvh *node)
{
	t_sphere	*sphere;

	if (node == NULL || node->object == NULL || node->object->object == NULL)
		return ;
	sphere = (t_sphere *)node->object->object;
	if (sphere->mat != NULL)
	{
		if (sphere->mat->img != NULL)
		{
			if (sphere->mat->img->image != NULL)
				mlx_destroy_image(get_mlx_ptr(), sphere->mat->img->image);
			free(sphere->mat->img);
		}
		if (sphere->mat->normal_map != NULL)
		{
			if (sphere->mat->normal_map->image != NULL)
				mlx_destroy_image(get_mlx_ptr(),
					sphere->mat->normal_map->image);
			free(sphere->mat->normal_map);
		}
		free(sphere->mat);
	}
	free(sphere);
}

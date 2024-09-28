/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 18:10:04 by ael-mank          #+#    #+#             */
/*   Updated: 2024/09/28 18:10:43 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	set_face_normal_cy(t_hitrecord *rec, t_ray *r, t_vec3 outward_normal)
{
	rec->front_face = dot(r->dir, outward_normal) < 0;
	if (rec->front_face)
		rec->normal = outward_normal;
	else
		rec->normal = vector_scale(outward_normal, -1);
}

double	hit_cylinder_wrapper(t_ray r, void *object, t_interval ray_t,
		t_hitrecord *rec)
{
	return (hit_cylinder(r, *(t_cylinder *)object, ray_t, rec));
}

void	free_cylinder(t_bvh *node)
{
	t_cylinder	*cylinder;

	cylinder = (t_cylinder *)node->object->object;
	if (cylinder->mat->img != NULL)
	{
		mlx_destroy_image(get_mlx_ptr(), cylinder->mat->img->image);
		free(cylinder->mat->img);
	}
	if (cylinder->mat != NULL)
		free(cylinder->mat);
	free(cylinder);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 19:11:34 by ael-mank          #+#    #+#             */
/*   Updated: 2024/09/28 20:38:33 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	hit_triangle_wrapper(t_ray r, void *object, t_interval ray_t,
		t_hitrecord *rec)
{
	return (hit_triangle(r, *(t_triangle *)object, ray_t, rec));
}

void	free_triangle(t_bvh *node)
{
	t_triangle	*triangle;

	triangle = (t_triangle *)node->object->object;
	if (triangle->mat->img != NULL)
	{
		mlx_destroy_image(get_mlx_ptr(), triangle->mat->img->image);
		free(triangle->mat->img);
	}
	if (triangle->mat != NULL)
		free(triangle->mat);
	free(triangle);
}

void	set_face_normal_triangle(t_hitrecord *rec, t_ray *r,
		t_triangle triangle)
{
	rec->normal = triangle.normal;
	rec->front_face = dot(r->dir, rec->normal) < 0;
	if (!rec->front_face)
	{
		rec->normal = vector_scale(rec->normal, -1);
	}
}

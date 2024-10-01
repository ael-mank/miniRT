/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_ray.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 10:16:58 by ael-mank          #+#    #+#             */
/*   Updated: 2024/10/01 09:23:38 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

t_vec3	ray_color(t_ray *r, int depth, t_bvh *bvh, t_scene *scene)
{
	t_hitrecord			rec;
	t_ray				scattered;
	t_scatter_params	params;
	t_vec3				vecs[3];

	ft_bzero(&rec, sizeof(t_hitrecord));
	if (depth <= 0)
		return (vec3(0, 0, 0));
	if (!bvh_hit(bvh, *r, universe_interval(), &rec))
		return (scene->bg_color);
	params.r = r;
	params.rec = &rec;
	params.attenuation = &vecs[0];
	params.scattered = &scattered;
	params.mat = rec.mat;
	if (!rec.mat->scatter(&params))
		return (rec.mat->emission(rec.mat, &rec));
	vecs[1] = vector_multiply(vecs[0], ray_color(&scattered, depth - 1, bvh,
				scene));
	vecs[2] = rec.mat->emission(rec.mat, &rec);
	return (vector_add(vector_add(vecs[1], vecs[2]), calculate_lighting(&rec,
				scene)));
}

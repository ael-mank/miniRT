/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_sim.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 20:46:05 by ael-mank          #+#    #+#             */
/*   Updated: 2024/09/28 20:46:13 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	reflect(t_vec3 v, t_vec3 n)
{
	return (vector_subtract(v, vector_scale(n, 2 * dot(v, n))));
}

t_vec3	refract(t_vec3 *uv, const t_vec3 *n, double etai_over_etat)
{
	double	cos_theta;
	t_vec3	r_out_perp;
	t_vec3	r_out_parallel;

	cos_theta = fmin(dot(vector_scale(*uv, -1), *n), 1.0);
	r_out_perp = vector_scale(vector_add(*uv, vector_scale(*n, cos_theta)),
			etai_over_etat);
	r_out_parallel = vector_scale(*n, -sqrt(fabs(1.0
					- vector_length_squared(r_out_perp))));
	return (vector_add(r_out_perp, r_out_parallel));
}

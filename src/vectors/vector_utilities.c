/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utilities.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 20:43:37 by ael-mank          #+#    #+#             */
/*   Updated: 2024/09/28 20:45:36 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "vectors.h"

/* Utility Functions */

int	near_zero(t_vec3 e)
{
	const double	s;

	s = 1e-8;
	return (fabs(e.x) < s && fabs(e.y) < s && fabs(e.z) < s);
}

t_vec3	random_in_unit_disk(void)
{
	t_vec3	p;

	while (1)
	{
		p = vec3(rand_double(-1, 1), rand_double(-1, 1), 0);
		if (vector_length_squared(p) < 1)
			break ;
	}
	return (p);
}

t_vec3	vector_min(t_vec3 a, t_vec3 b)
{
	return (vec3(fmin(a.x, b.x), fmin(a.y, b.y), fmin(a.z, b.z)));
}

t_vec3	vector_max(t_vec3 a, t_vec3 b)
{
	return (vec3(fmax(a.x, b.x), fmax(a.y, b.y), fmax(a.z, b.z)));
}

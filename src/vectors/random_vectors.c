/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_vectors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 20:43:17 by ael-mank          #+#    #+#             */
/*   Updated: 2024/09/28 20:45:16 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "vectors.h"

/* Random Vector Generation */

t_vec3	random_in_unit_sphere(void)
{
	t_vec3	p;

	while (1)
	{
		p = rand_vec(-1, 1);
		if (vector_length_squared(p) >= 1)
			return (p);
	}
}

t_vec3	random_on_hemisphere(t_vec3 normal)
{
	t_vec3	in_unit_sphere;

	in_unit_sphere = random_in_unit_sphere();
	if (dot(in_unit_sphere, normal) > 0.0)
		return (in_unit_sphere);
	else
		return (vector_scale(in_unit_sphere, -1));
}

t_vec3	random_unit_vector(void)
{
	double	a;
	double	z;
	double	r;

	a = ((double)rand() / RAND_MAX) * 2.0 * M_PI;
	z = ((double)rand() / RAND_MAX) * 2.0 - 1.0;
	r = sqrt(1.0 - z * z);
	return (vec3(r * cos(a), r * sin(a), z));
}

t_vec3	sample_square(void)
{
	return (vec3(random_double() - 0.5, random_double() - 0.5, 0));
}

t_vec3	rand_vec(double min, double max)
{
	return (vec3(rand_double(min, max), rand_double(min, max), rand_double(min,
				max)));
}

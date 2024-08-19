/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 13:41:32 by ael-mank          #+#    #+#             */
/*   Updated: 2024/08/19 11:04:45 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "vectors.h"

/* Vector Creation and Basic Operations */

t_vec3	vec3(double x, double y, double z)
{
	t_vec3	vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}

t_vec3	vector_add(t_vec3 a, t_vec3 b)
{
	return (vec3(a.x + b.x, a.y + b.y, a.z + b.z));
}

t_vec3	vector_subtract(t_vec3 a, t_vec3 b)
{
	return (vec3(a.x - b.x, a.y - b.y, a.z - b.z));
}

t_vec3	vector_scale(t_vec3 v, double scalar)
{
	return (vec3(v.x * scalar, v.y * scalar, v.z * scalar));
}

t_vec3	vector_divide(t_vec3 v, double scalar)
{
	return (vec3(v.x / scalar, v.y / scalar, v.z / scalar));
}

t_vec3	vector_multiply(t_vec3 a, t_vec3 b)
{
	return (vec3(a.x * b.x, a.y * b.y, a.z * b.z));
}

/* Vector Properties */

double	vector_length(t_vec3 v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

double	vector_length_squared(t_vec3 v)
{
	return (v.x * v.x + v.y * v.y + v.z * v.z);
}

t_vec3	vector_normalize(t_vec3 v)
{
	double	length;

	length = vector_length(v);
	if (length == 0)
	{
		return (vec3(0, 0, 0));
	}
	return (vec3(v.x / length, v.y / length, v.z / length));
}

t_vec3	unit_vector(t_vec3 v)
{
	return (vector_divide(v, vector_length(v)));
}

/* Vector Products */

double	dot(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

double	dot_product(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vec3	cross_product(t_vec3 a, t_vec3 b)
{
	t_vec3	result;

	result = vec3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y
			* b.x);
	return (result);
}

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

/* Utility Functions */

t_vec3	reflect(t_vec3 v, t_vec3 n)
{
	return (vector_subtract(v, vector_scale(n, 2 * dot_product(v, n))));
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

int	near_zero(t_vec3 e)
{
	const double	s = 1e-8;

	return (fabs(e.x) < s && fabs(e.y) < s && fabs(e.z) < s);
}

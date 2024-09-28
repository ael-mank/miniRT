/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_properties.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 20:42:41 by ael-mank          #+#    #+#             */
/*   Updated: 2024/09/28 20:45:06 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "vectors.h"

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

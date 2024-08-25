/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aabb.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 11:07:50 by ael-mank          #+#    #+#             */
/*   Updated: 2024/08/25 08:29:22 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_aabb	empty_aabb(void)
{
	t_aabb	aabb;

	aabb.x = (t_interval){0, 0};
	aabb.y = (t_interval){0, 0};
	aabb.z = (t_interval){0, 0};
	return (aabb);
}

t_interval expand(double delta, t_interval i)
{
	return (interval(i.min - delta, i.max + delta));
}

void pad_to_minimums(t_aabb *a)
{
	double	delta;

	delta = 0.0001;
	a->x = expand(delta, a->x);
	a->y = expand(delta, a->y);
	a->z = expand(delta, a->z);
}

t_aabb	aabb(t_interval x, t_interval y, t_interval z)
{
	t_aabb	aabb;

	aabb.x = x;
	aabb.y = y;
	aabb.z = z;
	pad_to_minimums(&aabb);
	return (aabb);
}

t_aabb	aabb_points(t_point3 a, t_point3 b)
{
	t_interval	x;
	t_interval	y;
	t_interval	z;

	x = interval(a.x, b.x);
	y = interval(a.y, b.y);
	z = interval(a.z, b.z);
	return (aabb(x, y, z));
}

t_aabb	aabb_aabb(t_aabb a, t_aabb b)
{
	t_interval	x;
	t_interval	y;
	t_interval	z;

	x = interval(fmin(a.x.min, b.x.min), fmax(a.x.max, b.x.max));
	y = interval(fmin(a.y.min, b.y.min), fmax(a.y.max, b.y.max));
	z = interval(fmin(a.z.min, b.z.min), fmax(a.z.max, b.z.max));
	return (aabb(x, y, z));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aabb.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 11:07:50 by ael-mank          #+#    #+#             */
/*   Updated: 2024/08/19 13:46:47 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_aabb empty_aabb(void)
{
	t_aabb	aabb;

	aabb.x = (t_interval){0, 0};
	aabb.y = (t_interval){0, 0};
	aabb.z = (t_interval){0, 0};
	return (aabb);
}

t_aabb	aabb(t_interval x, t_interval y, t_interval z)
{
	t_aabb	aabb;

	aabb.x = x;
	aabb.y = y;
	aabb.z = z;
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

t_aabb aabb_aabb(t_aabb a, t_aabb b)
{
	t_interval	x;
	t_interval	y;
	t_interval	z;

	x = interval(fmin(a.x.min, b.x.min), fmax(a.x.max, b.x.max));
	y = interval(fmin(a.y.min, b.y.min), fmax(a.y.max, b.y.max));
	z = interval(fmin(a.z.min, b.z.min), fmax(a.z.max, b.z.max));
	return (aabb(x, y, z));
}

t_interval	get_axis(t_aabb box, int axis)
{
	if (axis == 1)
		return (box.y);
	if (axis == 2)
		return (box.z);
	return (box.x);
}

int hit_interval(t_interval i, double origin, double direction, t_interval t)
{
	double	t0;
	double	t1;

	t0 = (i.min - origin) / direction;
	t1 = (i.max - origin) / direction;
	if (direction < 0)
	{
		double	temp;

		temp = t0;
		t0 = t1;
		t1 = temp;
	}
	t.min = fmax(t.min, t0);
	t.max = fmin(t.max, t1);
	if (t.min > t.max)
		return (0);
	return (1);
}

int hit_aabb(t_ray r, t_aabb box, t_interval ray_t)
{
    double t_min = ray_t.min;
    double t_max = ray_t.max;

    // X-axis
    double invDx = 1.0 / r.dir.x;
    double t0x = (box.x.min - r.org.x) * invDx;
    double t1x = (box.x.max - r.org.x) * invDx;
    if (invDx < 0.0) {
        double temp = t0x;
        t0x = t1x;
        t1x = temp;
    }
    t_min = t0x > t_min ? t0x : t_min;
    t_max = t1x < t_max ? t1x : t_max;
    if (t_max <= t_min)
        return 0;

    // Y-axis
    double invDy = 1.0 / r.dir.y;
    double t0y = (box.y.min - r.org.y) * invDy;
    double t1y = (box.y.max - r.org.y) * invDy;
    if (invDy < 0.0) {
        double temp = t0y;
        t0y = t1y;
        t1y = temp;
    }
    t_min = t0y > t_min ? t0y : t_min;
    t_max = t1y < t_max ? t1y : t_max;
    if (t_max <= t_min)
        return 0;

    // Z-axis
    double invDz = 1.0 / r.dir.z;
    double t0z = (box.z.min - r.org.z) * invDz;
    double t1z = (box.z.max - r.org.z) * invDz;
    if (invDz < 0.0) {
        double temp = t0z;
        t0z = t1z;
        t1z = temp;
    }
    t_min = t0z > t_min ? t0z : t_min;
    t_max = t1z < t_max ? t1z : t_max;
    if (t_max <= t_min)
        return 0;

    return 1;
}
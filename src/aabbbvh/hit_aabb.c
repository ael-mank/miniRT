/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_aabb.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 11:45:58 by ael-mank          #+#    #+#             */
/*   Updated: 2024/08/25 08:03:06 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	hit_interval(t_interval i, double origin, double direction, t_interval t)
{
	double	t0;
	double	t1;
	double	temp;

	t0 = (i.min - origin) / direction;
	t1 = (i.max - origin) / direction;
	if (direction < 0)
	{
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

static inline int	check_axis(t_check_axis_params params)
{
	double	invd;
	double	t0;
	double	t1;
	double	temp;

	invd = 1.0 / params.direction;
	t0 = (params.min - params.origin) * invd;
	t1 = (params.max - params.origin) * invd;
	if (invd < 0.0)
	{
		temp = t0;
		t0 = t1;
		t1 = temp;
	}
	if (t0 > *params.t_min)
		*params.t_min = t0;
	if (t1 < *params.t_max)
		*params.t_max = t1;
	return (*params.t_max > *params.t_min);
}

void	set_x_params(t_ray r, t_aabb box, t_check_axis_params *params)
{
	params->min = box.x.min;
	params->max = box.x.max;
	params->origin = r.org.x;
	params->direction = r.dir.x;
}

int	hit_aabb(t_ray r, t_aabb box, t_interval ray_t)
{
	double				t_min;
	double				t_max;
	t_check_axis_params	params;

	t_min = ray_t.min;
	t_max = ray_t.max;
	params.t_min = &t_min;
	params.t_max = &t_max;
	set_x_params(r, box, &params);
	if (!check_axis(params))
		return (0);
	params.min = box.y.min;
	params.max = box.y.max;
	params.origin = r.org.y;
	params.direction = r.dir.y;
	if (!check_axis(params))
		return (0);
	params.min = box.z.min;
	params.max = box.z.max;
	params.origin = r.org.z;
	params.direction = r.dir.z;
	if (!check_axis(params))
		return (0);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 14:06:12 by ael-mank          #+#    #+#             */
/*   Updated: 2024/08/08 13:06:20 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ray_init(t_ray *r, const t_point3 *origin, const t_point3 *direction)
{
	if (r == NULL || origin == NULL || direction == NULL)
	{
		return ;
	}
	r->org = *origin;
	r->dir = *direction;
}

const t_point3	*ray_origin(t_ray *r)
{
	if (r == NULL)
	{
		return (NULL);
	}
	return (&r->org);
}

const t_point3	*ray_direction(t_ray *r)
{
	if (r == NULL)
	{
		return (NULL);
	}
	return (&r->dir);
}

t_point3	ray_at(const t_ray *r, double t)
{
	t_point3	default_coord;

	default_coord.x = 0;
	default_coord.y = 0;
	default_coord.z = 0;
	if (r == NULL)
	{
		return (default_coord);
	}
	return (vector_add(r->org, vector_scale(r->dir, t)));
}

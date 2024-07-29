/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 14:06:12 by ael-mank          #+#    #+#             */
/*   Updated: 2024/07/29 14:08:55 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "ray.h"

void	ray_init(ray *r, const t_coord *origin, const t_coord *direction)
{
	if (r == NULL || origin == NULL || direction == NULL)
	{
		return ;
	}
	r->orig = *origin;
	r->dir = *direction;
}

const t_coord	*ray_origin(const ray *r)
{
	if (r == NULL)
	{
		return (NULL);
	}
	return (&r->orig);
}

const t_coord	*ray_direction(const ray *r)
{
	if (r == NULL)
	{
		return (NULL);
	}
	return (&r->dir);
}

t_coord	ray_at(const ray *r, double t)
{
	t_coord	default_coord;

	default_coord.x = 0;
	default_coord.y = 0;
	default_coord.z = 0;
	if (r == NULL)
	{
		return (default_coord);
	}
	return (v_add(r->orig, v_scale(r->dir, t)));
}

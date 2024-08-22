/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aabb.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 11:06:53 by ael-mank          #+#    #+#             */
/*   Updated: 2024/08/22 09:48:12 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AABB_H
# define AABB_H

#include "minirt.h"
#include "interval.h"
#include "vectors.h"

typedef struct s_aabb t_aabb;

typedef struct s_aabb
{
	t_interval x;
	t_interval y;
	t_interval z;
	int (*hit)(t_ray r, t_aabb box, t_interval ray_t);
}	t_aabb;

typedef struct s_check_axis_params
{
    double min;
    double max;
    double origin;
    double direction;
    double *t_min;
    double *t_max;
}	t_check_axis_params;


t_aabb		aabb(t_interval x, t_interval y, t_interval z);
t_aabb		empty_aabb(void);
t_aabb		aabb_points(t_point3 a, t_point3 b);
t_aabb		aabb_aabb(t_aabb a, t_aabb b);
t_interval	get_axis(t_aabb box, int axis);
int			hit_aabb(t_ray r, t_aabb box, t_interval ray_t);

#endif

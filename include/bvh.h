/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 11:25:35 by ael-mank          #+#    #+#             */
/*   Updated: 2024/08/19 12:39:34 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BVH_H
# define BVH_H

#include "minirt.h"

typedef struct s_bvh t_bvh;

typedef struct s_bvh
{
	t_aabb		box;
	int			(*hit)(t_bvh *node, t_ray r, t_interval ray_t, t_hitrecord *rec);
	struct s_bvh	*left;
	struct s_bvh	*right;
	t_object	*object;
}	t_bvh;


void print_bvh_tree(t_bvh *node, int level);
t_bvh *create_bvh_node(t_object *objects);
int bvh_hit(t_bvh *node, t_ray r, t_interval ray_t, t_hitrecord *rec);

#endif
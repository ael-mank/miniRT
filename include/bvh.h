/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 11:25:35 by ael-mank          #+#    #+#             */
/*   Updated: 2024/08/21 14:20:50 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BVH_H
# define BVH_H

# include "minirt.h"

typedef struct s_bvh	t_bvh;

typedef struct s_bvh
{
	t_aabb				box;
	int					(*hit)(t_bvh *node, t_ray r, t_interval ray_t,
								t_hitrecord *rec);
	struct s_bvh		*left;
	struct s_bvh		*right;
	t_object			*object;
}						t_bvh;

void					print_bvh_tree(t_bvh *node, int level);
t_bvh					*create_bvh_node(t_object *objects);
int						bvh_hit(t_bvh *node, t_ray r, t_interval ray_t,
							t_hitrecord *rec);
t_object				*sorted_insert(t_object *sorted, t_object *new_node,
							int (*comparator)(const void *, const void *));
int	compare_objects(const void *a, const void *b, int axis);
int				box_x_compare(const void *a, const void *b);
int				box_y_compare(const void *a, const void *b);
int				box_z_compare(const void *a, const void *b);
int compare_objects_x(const void *a, const void *b);
int compare_objects_y(const void *a, const void *b);
int compare_objects_z(const void *a, const void *b);
size_t					count_objects(t_object *objects);
t_object	*insertion_sort(t_object *head, int (*comparator)(const void *,
			const void *));

#endif
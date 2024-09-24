/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 11:25:35 by ael-mank          #+#    #+#             */
/*   Updated: 2024/09/24 15:43:32 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BVH_H
# define BVH_H

# include "minirt.h"
# include "objects.h"
# include <stddef.h>

typedef struct s_bvh	t_bvh;

typedef struct s_bvh
{
	t_aabb			box;
	int				(*hit)(t_bvh *node, t_ray r, t_interval ray_t,
					t_hitrecord *rec);
	struct s_bvh	*left;
	struct s_bvh	*right;
	t_object		*object;
}						t_bvh;

// Function prototypes for BVH operations
void					print_bvh_tree(t_bvh *node, int level);
// Print the BVH tree
t_bvh					*create_bvh_node(t_object *objects);
// Create a BVH node from a list of objects
int						bvh_hit(t_bvh *node, t_ray r, t_interval ray_t,
							t_hitrecord *rec);
// Check if a ray hits the BVH node

// Function prototypes for object sorting
t_object				*sorted_insert(t_object *sorted, t_object *new_node,
							int (*comparator)(const void *, const void *));
// Insert an object into a sorted list
t_object				*insertion_sort(t_object *head,
							int (*comparator)(const void *, const void *));
// Sort a list of objects using insertion sort
size_t					count_objects(t_object *objects);
// Count the number of objects in a list

// Function prototypes for object comparison
int						compare_objects(const void *a, const void *b, int axis);
// Compare two objects along a specified axis
int						box_x_compare(const void *a, const void *b);
// Compare two objects along the x-axis
int						box_y_compare(const void *a, const void *b);
// Compare two objects along the y-axis
int						box_z_compare(const void *a, const void *b);
// Compare two objects along the z-axis
int						compare_objects_x(const void *a, const void *b);
// Compare two objects along the x-axis (alternative)
int						compare_objects_y(const void *a, const void *b);
// Compare two objects along the y-axis (alternative)
int						compare_objects_z(const void *a, const void *b);
// Compare two objects along the z-axis (alternative)

#endif
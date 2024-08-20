/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 11:28:31 by ael-mank          #+#    #+#             */
/*   Updated: 2024/08/20 22:36:38 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// void print_indent(int level) {
//     for (int i = 0; i < level; i++) {
//         printf("  ");
//     }
// }

// void print_bvh_tree(t_bvh *node, int level) {
//     if (node == NULL) {
//         print_indent(level);
//         printf("NULL\n");
//         return;
//     }

//     print_indent(level);
//     printf("BVH Node:\n");

//     print_indent(level + 1);
//     printf("Box: AABB(min: [%.2f, %.2f, %.2f], max: [%.2f, %.2f, %.2f])\n",
//            node->box.x.min, node->box.y.min, node->box.z.min,
//            node->box.x.max, node->box.y.max, node->box.z.max);

//     print_indent(level + 1);
//     if (node->object != NULL) {
//         printf("Object: Object at address: %p\n", (void *)node->object);
//     } else {
//         printf("Object: No object\n");
//     }

//     if (node->left || node->right) {
//         print_indent(level);
//         printf("├─ Left:\n");
//         print_bvh_tree(node->left, level + 1);

//         print_indent(level);
//         printf("└─ Right:\n");
//         print_bvh_tree(node->right, level + 1);
//     }
// }

int	bvh_hit_check_box(t_bvh *node, t_ray r, t_interval ray_t)
{
	if (!node->box.hit(r, node->box, ray_t))
	{
		return (0);
	}
	return (1);
}

int	bvh_hit_node(t_bvh *node, t_ray r, t_interval ray_t, t_hitrecord *rec)
{
	t_hitrecord	left_rec;
	int			hit_left;
	t_interval	right_t;
	t_hitrecord	right_rec;
	int			hit_right;

	if (node->object && !node->left && !node->right)
	{
		return (node->object->hit(r, node->object->object, ray_t, rec));
	}
	hit_left = 0;
	if (node->left)
	{
		hit_left = bvh_hit(node->left, r, ray_t, &left_rec);
	}
	if (hit_left)
	{
		right_t = (t_interval){ray_t.min, left_rec.t};
	}
	else
	{
		right_t = ray_t;
	}
	hit_right = 0;
	if (node->right)
	{
		hit_right = bvh_hit(node->right, r, right_t, &right_rec);
	}
	if (hit_left && hit_right)
	{
		if (left_rec.t < right_rec.t)
		{
			*rec = left_rec;
		}
		else
		{
			*rec = right_rec;
		}
		return (1);
	}
	else if (hit_left)
	{
		*rec = left_rec;
		return (1);
	}
	else if (hit_right)
	{
		*rec = right_rec;
		return (1);
	}
	return (0);
}

int	bvh_hit(t_bvh *node, t_ray r, t_interval ray_t, t_hitrecord *rec)
{
	if (!node)
		return (0);

	if (!bvh_hit_check_box(node, r, ray_t))
		return (0);
	return (bvh_hit_node(node, r, ray_t, rec));
}
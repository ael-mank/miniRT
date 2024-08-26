/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 11:28:31 by ael-mank          #+#    #+#             */
/*   Updated: 2024/08/26 09:39:38 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void print_indent(int level) {
    for (int i = 0; i < level; i++) {
        printf("  ");
    }
}

void print_bvh_tree(t_bvh *node, int level) {
    if (node == NULL) {
        print_indent(level);
        printf("NULL\n");
        return;
    }

    print_indent(level);
    printf("{\n");

    print_indent(level + 1);
    printf("\"min\": [%.2f, %.2f, %.2f],\n", node->box.x.min, node->box.y.min, node->box.z.min);

    print_indent(level + 1);
    printf("\"max\": [%.2f, %.2f, %.2f],\n", node->box.x.max, node->box.y.max, node->box.z.max);

    print_indent(level + 1);
    if (node->object != NULL) {
        printf("\"object\": \"%p\",\n", (void *)node->object);
    } else {
        printf("\"object\": null,\n");
    }

    print_indent(level + 1);
    printf("\"children\": [\n");

    if (node->left || node->right) {
        print_bvh_tree(node->left, level + 2);
        printf(",\n");
        print_bvh_tree(node->right, level + 2);
    }

    print_indent(level + 1);
    printf("]\n");

    print_indent(level);
    printf("}");
}

static inline int	bvh_hit_check_box(t_bvh *node, t_ray r, t_interval ray_t)
{
	return (node->box.hit(r, node->box, ray_t));
}

static inline int	bvh_hit_node(t_bvh *node, t_ray r, t_interval ray_t, t_hitrecord *rec)
{
	t_hitrecord	left_rec;
	t_hitrecord	right_rec;
	t_interval	right_t;

	int (hit_left) = 0;
	int (hit_right) = 0;
	right_t = ray_t;
	if (node->object && !node->left && !node->right)
		return (node->object->hit(r, node->object->object, ray_t, rec));
	if (node->left)
		hit_left = bvh_hit(node->left, r, ray_t, &left_rec);
	if (hit_left)
		right_t = (t_interval){ray_t.min, left_rec.t};
	if (node->right)
		hit_right = bvh_hit(node->right, r, right_t, &right_rec);
	if (hit_left && hit_right)
	{
		if (left_rec.t < right_rec.t)
			*rec = left_rec;
		else
			*rec = right_rec;
	}
	else if (hit_left)
		*rec = left_rec;
	else if (hit_right)
		*rec = right_rec;
	else
		return (0);
	return (1);
}

int	bvh_hit(t_bvh *node, t_ray r, t_interval ray_t, t_hitrecord *rec)
{
	if (!node || !bvh_hit_check_box(node, r, ray_t))
		return (0);
	return (bvh_hit_node(node, r, ray_t, rec));
}

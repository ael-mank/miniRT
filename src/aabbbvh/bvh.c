/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 11:28:31 by ael-mank          #+#    #+#             */
/*   Updated: 2024/08/20 17:08:53 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void print_indent(int level)
{
    for (int i = 0; i < level; i++)
    {
        printf("  ");
    }
}

void print_bvh_tree(t_bvh *node, int level)
{
    if (node == NULL)
    {
        print_indent(level);
        printf("NULL\n");
        return;
    }

    print_indent(level);
    printf("BVH Node:\n");

    print_indent(level + 1);
    printf("Box: AABB(min: [%.2f, %.2f, %.2f], max: [%.2f, %.2f, %.2f])\n",
           node->box.x.min, node->box.y.min, node->box.z.min,
           node->box.x.max, node->box.y.max, node->box.z.max);

    print_indent(level + 1);
    if (node->object != NULL)
    {
        printf("Object: Object at address: %p\n", (void *)node->object);
    }
    else
    {
        printf("Object: No object\n");
    }

    print_indent(level + 1);
    printf("Left:\n");
    print_bvh_tree(node->left, level + 2);

    print_indent(level + 1);
    printf("Right:\n");
    print_bvh_tree(node->right, level + 2);
}

size_t	count_objects(t_object *objects)
{
	size_t	count;

	count = 0;
	while (objects)
	{
		count++;
		objects = objects->next;
	}
	return (count);
}

t_object	*split_list(t_object *objects, size_t mid)
{
	t_object	*current;
	size_t			i;

	i = 0;
	current = objects;
	while (i < mid - 1)
	{
		current = current->next;
		i++;
	}
	t_object *second_half = current->next;
	current->next = NULL;
	return (second_half);
}

t_object *sorted_insert(t_object *sorted, t_object *new_node, int (*comparator)(const void *, const void *))
{
    if (!sorted || comparator(&new_node, &sorted) < 0)
    {
        new_node->next = sorted;
        return new_node;
    }
    t_object *current = sorted;
    while (current->next && comparator(&new_node, &current->next) >= 0)
    {
        current = current->next;
    }
    new_node->next = current->next;
    current->next = new_node;
    return sorted;
}

t_object *insertion_sort(t_object *head, int (*comparator)(const void *, const void *))
{
    t_object *sorted = NULL;
    t_object *current = head;
    while (current)
    {
        t_object *next = current->next;
        sorted = sorted_insert(sorted, current, comparator);
        current = next;
    }
    return sorted;
}

static int box_x_compare(const void *a, const void *b)
{
	t_object *object_a = *(t_object **)a;
	t_object *object_b = *(t_object **)b;
	t_aabb box_a = object_a->box;
	t_aabb box_b = object_b->box;
	return (box_a.x.min - box_b.x.min) < 0.0;
}

static int box_y_compare(const void *a, const void *b)
{
	t_object *object_a = *(t_object **)a;
	t_object *object_b = *(t_object **)b;
	t_aabb box_a = object_a->box;
	t_aabb box_b = object_b->box;
	return (box_a.y.min - box_b.y.min) < 0.0;
}

static int box_z_compare(const void *a, const void *b)
{
	t_object *object_a = *(t_object **)a;
	t_object *object_b = *(t_object **)b;
	t_aabb box_a = object_a->box;
	t_aabb box_b = object_b->box;
	return (box_a.z.min - box_b.z.min) < 0.0;
}

int bvh_hit(t_bvh *node, t_ray r, t_interval ray_t, t_hitrecord *rec)
{
    if (!node)
        return 0;

    // Check if the ray intersects the bounding box of the current node
    if (!node->box.hit(r, node->box, ray_t))
        return 0;

    int hit_left = 0;
    int hit_right = 0;
    t_hitrecord left_rec, right_rec;

    // If it's a leaf node with an object, check for intersection
    if (node->object && !node->left && !node->right)
    {
        if (node->object->hit == NULL)
            write(1, "NULL\n", 5);
        return node->object->hit(r, node->object->object, ray_t, rec);
    }

    // Check left child if it exists
    if (node->left)
    {
        hit_left = bvh_hit(node->left, r, ray_t, &left_rec);
    }

    // Check right child if it exists
    if (node->right)
    {
        // If we hit the left child, update the ray_t.max to potentially reduce computation
        t_interval right_t = hit_left ? (t_interval){ray_t.min, left_rec.t} : ray_t;
        hit_right = bvh_hit(node->right, r, right_t, &right_rec);
    }

    // Return the closest hit
    if (hit_left && hit_right)
    {
        *rec = (left_rec.t < right_rec.t) ? left_rec : right_rec;
        return 1;
    }
    else if (hit_left)
    {
        *rec = left_rec;
        return 1;
    }
    else if (hit_right)
    {
        *rec = right_rec;
        return 1;
    }

    return 0;
}

t_bvh *create_bvh_node(t_object *objects)
{
    t_bvh *node = malloc(sizeof(t_bvh));
    if (node == NULL)
    {
        return NULL;
    }

    size_t object_count = count_objects(objects);
    if (object_count == 0)
    {
        free(node);
        return NULL;
    }

    int axis = rand() % 3;
    int (*comparator)(const void *, const void *) = (axis == 0) ? box_x_compare
                                      : (axis == 1) ? box_y_compare
                                                    : box_z_compare;

    if (object_count == 1)
    {
        node->left = node->right = NULL;
        node->object = objects;
        node->box = objects->box;
        node->box.hit = hit_aabb;
        node->hit = bvh_hit;
    }
    else if (object_count == 2)
    {
        if (comparator(&objects, &objects->next) > 0)
        {
            t_object *temp = objects;
            objects = objects->next;
            objects->next = temp;
            temp->next = NULL;
        }
        node->left = malloc(sizeof(t_bvh));
        node->right = malloc(sizeof(t_bvh));
        if (node->left == NULL || node->right == NULL)
        {
            free(node->left);
            free(node->right);
            free(node);
            return NULL;
        }
        node->left->object = objects;
        node->right->object = objects->next;
        node->left->left = node->left->right = NULL;
        node->right->left = node->right->right = NULL;
        node->left->box = objects->box;
        node->right->box = objects->next->box;
        node->left->box.hit = hit_aabb;
        node->right->box.hit = hit_aabb;
        node->left->hit = bvh_hit;
        node->right->hit = bvh_hit;
        node->box = aabb_aabb(node->left->box, node->right->box);
        node->box.hit = hit_aabb;
        node->hit = bvh_hit;
        node->object = NULL;
    }
    else
    {
        objects = insertion_sort(objects, comparator);
        size_t mid = object_count / 2;
        t_object *second_half = split_list(objects, mid);
        node->left = create_bvh_node(objects);
        node->right = create_bvh_node(second_half);
        if (node->left == NULL || node->right == NULL)
        {
            free(node->left);
            free(node->right);
            free(node);
            return NULL;
        }
        node->box = aabb_aabb(node->left->box, node->right->box);
        node->box.hit = hit_aabb;
		if (objects->hit == NULL)
		 	write(1, "NULL\n", 5);
        node->hit = bvh_hit;
        node->object = NULL;
    }

    return node;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 08:57:27 by ael-mank          #+#    #+#             */
/*   Updated: 2024/08/20 17:20:34 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_scene(t_object *objects)
{
	t_object	*current;
	t_object	*next;

	current = objects;
	while (current)
	{
		next = current->next;
		free(current->mat);
		free(current->object);
		free(current);
		current = next;
	}
}

//TODO : GIVE EACH OBJECT A FREE FUNCTION
void free_bvh_tree(t_bvh *node) {
    if (node == NULL) {
        return;
    }

    // Recursively free the left and right subtrees
    free_bvh_tree(node->left);
    free_bvh_tree(node->right);

    // Check if node->object and node->object->object are not NULL
    if (node->object != NULL && node->object->object != NULL) {
        // Cast node->object->object to t_sphere* and free its members
        t_sphere *sphere = (t_sphere *)node->object->object;
        if (sphere->mat != NULL) {
            free(sphere->mat);  // Assuming mat is a member of t_sphere
        }
        free(sphere);
    }

    // Free the current node
    free(node->object);
    free(node);
}

int	ft_exit(t_scene *scene)
{
	t_mlx	*mlx;

	mlx = &scene->mlx;
	//free_scene(scene->objects);
	free_bvh_tree(scene->bvh);
	mlx_destroy_image(mlx->mlx_ptr, mlx->img.img);
	mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
	mlx_destroy_display(mlx->mlx_ptr);
	free(mlx->mlx_ptr);
	printf("\033[1;32mClosed by User.\033[0m\n");
	exit(0);
}

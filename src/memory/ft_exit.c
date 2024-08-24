/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 08:57:27 by ael-mank          #+#    #+#             */
/*   Updated: 2024/08/24 17:56:49 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// void	free_scene(t_object *objects)
// {
// 	t_object	*current;
// 	t_object	*next;

// 	current = objects;
// 	while (current)
// 	{
// 		next = current->next;
// 		free(current->mat);
// 		free(current->object);
// 		free(current);
// 		current = next;
// 	}
// }
//TODO : GIVE EACH OBJECT A FREE FUNCTION

void	free_sphere(t_bvh *node)
{
	t_sphere	*sphere;

	sphere = (t_sphere *)node->object->object;
	if (sphere->mat->img != NULL)
	{
		mlx_destroy_image(get_mlx_ptr(), sphere->mat->img->image);
		free(sphere->mat->img);
	}
	if (sphere->mat != NULL)
		free(sphere->mat);
	free(sphere);
}
void	free_bvh_tree(t_bvh *node)
{
	if (node == NULL)
		return ;
	free_bvh_tree(node->left);
	free_bvh_tree(node->right);
	if (node->object != NULL && node->object->object != NULL)
	{
		node->object->free(node);
	}
	free(node->object);
	free(node);
}

int	ft_exit(t_scene *scene)
{
	t_mlx	*mlx;

	mlx = &scene->mlx;
	free_bvh_tree(scene->bvh);
	mlx_destroy_image(mlx->mlx_ptr, mlx->img.img);
	mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
	mlx_destroy_display(mlx->mlx_ptr);
	free(mlx->mlx_ptr);
	printf("\033[1;32mClosed by User.\033[0m\n");
	exit(0);
}

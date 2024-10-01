/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 08:57:27 by ael-mank          #+#    #+#             */
/*   Updated: 2024/10/01 09:35:58 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_bvh_tree(t_bvh *node)
{
	if (node == NULL)
		return ;
	free_bvh_tree(node->left);
	free_bvh_tree(node->right);
	if (node->object != NULL && node->object->object != NULL)
		node->object->free(node);
	free(node->object);
	free(node);
}

void	free_ligts(t_point_light *lights)
{
	t_point_light	*current;
	t_point_light	*next;

	current = lights;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
}

int	ft_exit(t_scene *scene)
{
	t_mlx	*mlx;

	mlx = &scene->mlx;
	free_bvh_tree(scene->bvh);
	if (mlx->img.img != NULL)
		mlx_destroy_image(mlx->mlx_ptr, mlx->img.img);
	if (mlx->win_ptr != NULL)
		mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
	if (mlx->mlx_ptr != NULL)
	{
		mlx_destroy_display(mlx->mlx_ptr);
		free(mlx->mlx_ptr);
	}
	free_ligts(scene->lights);
	ft_lstclear(&scene->lst_map, free);
	close(scene->file_fd);
	printf("\033[1;32mSuccessfuly left miniRT.\033[0m\n");
	exit(0);
}

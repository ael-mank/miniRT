/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 08:57:27 by ael-mank          #+#    #+#             */
/*   Updated: 2024/09/23 09:56:53 by ael-mank         ###   ########.fr       */
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

void	free_cylinder(t_bvh *node)
{
	t_cylinder	*cylinder;

	cylinder = (t_cylinder *)node->object->object;
	if (cylinder->mat->img != NULL)
	{
		mlx_destroy_image(get_mlx_ptr(), cylinder->mat->img->image);
		free(cylinder->mat->img);
	}
	if (cylinder->mat != NULL)
		free(cylinder->mat);
	free(cylinder);
}

void	free_plane(t_bvh *node)
{
	t_plane	*plane;

	plane = (t_plane *)node->object->object;
	if (plane->mat->img != NULL)
	{
		mlx_destroy_image(get_mlx_ptr(), plane->mat->img->image);
		free(plane->mat->img);
	}
	if (plane->mat != NULL)
		free(plane->mat);
	free(plane);
}

void	free_triangle(t_bvh *node)
{
	t_triangle	*triangle;

	triangle = (t_triangle *)node->object->object;
	if (triangle->mat->img != NULL)
	{
		mlx_destroy_image(get_mlx_ptr(), triangle->mat->img->image);
		free(triangle->mat->img);
	}
	if (triangle->mat != NULL)
		free(triangle->mat);
	free(triangle);
}

void	free_quad(t_bvh *node)
{
	t_quad	*quad;

	quad = (t_quad *)node->object->object;
	if (quad->mat->img != NULL)
	{
		mlx_destroy_image(get_mlx_ptr(), quad->mat->img->image);
		free(quad->mat->img);
	}
	if (quad->mat != NULL)
		free(quad->mat);
	free(quad);
}

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
		node->object->free(node);
	free(node->object);
	free(node);
}

void free_ligts(t_point_light *lights)
{
	t_point_light *current;
	t_point_light *next;

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
	printf("\033[1;32mSuccessfuly left miniRT.\033[0m\n");
	exit(0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 08:57:27 by ael-mank          #+#    #+#             */
/*   Updated: 2024/08/10 18:11:32 by ael-mank         ###   ########.fr       */
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
		free(current->object);
		free(current);
		current = next;
	}
}

int	ft_exit(t_scene *scene)
{
	t_mlx *mlx;

	mlx = &scene->mlx;
	free_scene(scene->objects);
	mlx_destroy_image(mlx->mlx_ptr, mlx->img.img);
	//first destroy images if used with mlx_destroy_image
	//then destroy window
	mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
	//destroy display
	mlx_destroy_display(mlx->mlx_ptr);
	free(mlx->mlx_ptr);
	printf("\033[1;32mClosed by User.\033[0m\n");
	exit(0);
}
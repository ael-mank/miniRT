/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 21:30:38 by ael-mank          #+#    #+#             */
/*   Updated: 2024/08/24 12:40:40 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	*get_mlx_ptr(void)
{
	static void	*mlx_ptr = NULL;

	if (!mlx_ptr)
		mlx_ptr = mlx_init();
	return (mlx_ptr);
}

void	init_mlx(t_scene *scene, int win_width, int win_height)
{
	t_mlx	*mlx;
	t_data	*img;

	mlx = &scene->mlx;
	img = &mlx->img;
	ft_bzero(&scene->mlx, sizeof(t_mlx));
	mlx->mlx_ptr = get_mlx_ptr();
	if (!mlx->mlx_ptr)
		exit(EXIT_FAILURE);
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, win_width, win_height,
			"MiniRT");
	if (!mlx->win_ptr)
		exit(EXIT_FAILURE);
	img->img = mlx_new_image(mlx->mlx_ptr, scene->render.image_width,
			scene->render.image_height);
	img->addr = mlx_get_data_addr(img->img, &img->bpp,
			&img->line_length, &img->endian);
	img->samples_per_pixel = scene->camera.samples_per_pixel;
}

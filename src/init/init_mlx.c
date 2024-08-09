/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 21:30:38 by ael-mank          #+#    #+#             */
/*   Updated: 2024/08/09 22:19:06 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_mlx(t_scene *scene, int win_width, int win_height)
{
	t_mlx *mlx;
	t_data *img;

	mlx = &scene->mlx;
	img = &mlx->img;
	ft_bzero(&scene->mlx, sizeof(t_mlx));
	mlx->mlx_ptr = mlx_init();
	if (!mlx->mlx_ptr)
		exit(EXIT_FAILURE);
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, win_width, win_height,
			"MiniRT");
	if (!mlx->win_ptr)
		exit(EXIT_FAILURE);
	img->img = mlx_new_image(mlx->mlx_ptr, scene->render.image_width,
			scene->render.image_height);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
}
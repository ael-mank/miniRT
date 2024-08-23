/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 08:42:04 by ael-mank          #+#    #+#             */
/*   Updated: 2024/08/23 11:14:42 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//FILE *out;
int	main(void)
{
	t_scene	scene;
	int		win_width;
	int		win_height;
	int		x;
	int		y;

	ft_bzero(&scene, sizeof(t_scene));
	win_width = 960;
	win_height = 540;
	init_scene(&scene);
	init_mlx(&scene, win_width, win_height);
	render_scene(&scene);
	x = (win_width - scene.render.image_width) / 2;
	y = (win_height - scene.render.image_height) / 2;
	printf("x: %d, y: %d\n", x, y);
	mlx_key_hook(scene.mlx.win_ptr, keys_handler, &scene);
	mlx_hook(scene.mlx.win_ptr, 17, 0, ft_exit, &scene);
	mlx_loop(scene.mlx.mlx_ptr);
}

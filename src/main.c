/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 08:42:04 by ael-mank          #+#    #+#             */
/*   Updated: 2024/09/27 22:53:04 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_rt(t_scene *scene, char **argv)
{
	int		win_width;
	int		win_height;

	(void)argv;
	ft_bzero(scene, sizeof(t_scene));
	win_width = 960;
	win_height = 540;
	init_scene(scene, argv);
	init_mlx(scene, win_width, win_height);
}

int	main(int argc, char **argv)
{
	t_scene	scene;

	(void)argv;
	if (argc != 2)
	{
		ft_printf("\033[0;31mError\n");
		ft_printf("Usage: ./miniRT [scene.rt]\n\033[0m");
		return (0);
	}
	else
	{
		init_rt(&scene, argv);
		render_scene(&scene);
		//save_image(&scene);
		mlx_key_hook(scene.mlx.win_ptr, keys_handler, &scene);
		mlx_hook(scene.mlx.win_ptr, 17, 0, ft_exit, &scene);
		mlx_loop(scene.mlx.mlx_ptr);
	}
}

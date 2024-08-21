/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrigny <yrigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 08:42:04 by ael-mank          #+#    #+#             */
/*   Updated: 2024/08/21 18:31:25 by yrigny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	calculate_image(t_win *win)
{
	int		x;
	int		y;
	char	*dst;

	x = -1;
	y = -1;
	if (win->render == 0)
		return (0);
	while (++y <= HEIGHT)
	{
		while (++x <= LENGTH)
		{
			dst = win->img.addr + (y * win->img.line_length + x
					* (win->img.bits_per_pixel / 8));
			*(unsigned int *)dst = calculate_pixel(x, y, *win->scene);
		}
		x = 0;
	}
	mlx_put_image_to_window(win->mlx, win->mlx_win, win->img.img, 0, 0);
	win->render = 0;
	return (0);
}

void	win_init(t_win *win, t_scene *scene)
{
	win->mlx = mlx_init();
	if (win->mlx == NULL)
		exit(1);
	win->mlx_win = mlx_new_window(win->mlx, LENGTH, HEIGHT, "miniRT");
	if (win->mlx_win == NULL)
	{
		free(win->mlx);
		exit(1);
	}
	win->scene = scene;
	win->img.img = mlx_new_image(win->mlx, LENGTH, HEIGHT);
	if (win->img.img == NULL)
	{
		free(win->mlx);
		free(win->mlx_win);
		exit(1);
	}
	win->img.addr = mlx_get_data_addr(win->img.img, &win->img.bits_per_pixel,
			&win->img.line_length, &win->img.endian);
	win->render = 1;
}

void	scene_init(t_scene *scene)
{
	scene->l = light_init();
	scene->c = cam_init();
	scene->v = viewport_init(scene->c);
	scene->sp = sphere_init();
}

int main(void)
{
	t_win	win;
	t_scene	scene;

	scene_init(&scene);
	win_init(&win, &scene);
	mlx_loop_hook(win.mlx, calculate_image, &win);
	mlx_hook(win.mlx_win, 17, 1L << 5, win_close, &win);
	mlx_hook(win.mlx_win, 2, 1L << 0, key_event, &win);
	mlx_loop(win.mlx);
	mlx_destroy_display(win.mlx);
	free(win.mlx);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrigny <yrigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:51:25 by yrigny            #+#    #+#             */
/*   Updated: 2024/09/17 22:45:18 by yrigny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	win_close(t_win *win)
{
	mlx_destroy_image(win->mlx, win->img.img);
	mlx_destroy_window(win->mlx, win->mlx_win);
	mlx_destroy_display(win->mlx);
	free(win->mlx);
	free_scene(win->scene);
	exit(0);
	return (0);
}

int	key_event(int key, t_win *win)
{
	if (key == XK_Escape)
		win_close(win);
	win->render = 1;
	return (0);
}

void	free_scene(t_scene *scene)
{
	t_obj	*head;
	t_obj	*temp;

	if (scene->a)
		free(scene->a);
	if (scene->c)
		free(scene->c);
	if (scene->l)
		free(scene->l);
	head = scene->objs;
	while (head)
	{
		temp = head->next;
		free(head->obj);
		ft_bzero(head, sizeof(t_list));
		free(head);
		head = temp;
	}
}
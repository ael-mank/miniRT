/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrigny <yrigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:51:25 by yrigny            #+#    #+#             */
/*   Updated: 2024/09/24 20:31:40 by yrigny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	open_file(int ac, char **av)
{
	int	fd;
	int	len;

	if (ac != 2 || av[1] == NULL)
	{
		ft_putstr_fd("Usage: ./miniRT *.rt\n", 1);
		exit(0);
	}
	len = ft_strlen(av[1]);
	if (ft_strnstr(av[1], ".rt", ft_strlen(av[1])) != av[1] + len - 3)
	{
		ft_putstr_fd("Error: Input must be .rt suffixed file\n", 2);
		exit(0);
	}
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Error: ", 2);
		perror(av[1]);
	}
	return (fd);
}

int	key_event(int key, t_win *win)
{
	if (key == XK_Escape)
		win_close(win);
	win->render = 1;
	return (0);
}

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

bool	err(char *obj, t_err_type err)
{
	char	*detail;

	detail = NULL;
	if (err == REPETITION)
		detail = "can't be declared more than once.\n";
	else if (err == RATIO)
		detail = "must be a number in range [0.0,1.0]\n";
	else if (err == POINT)
		detail = "must be 3 numbers in format (x,y,z)\n";
	else if (err == COLOR)
		detail = "must be 3 integers in format (r,g,b) in range [0,255]\n";
	else if (err == POS_NUM)
		detail = "must be a positive number\n";
	else if (err == DIRECTION)
		detail = "must be 3 numbers in format (x,y,z) in range [-1,1]\n";
	else if (err == FOV)
		detail = "must be a number in range [0,180]\n";
	else if (err == NOISE)
		detail = "has noise information\n";
	printf("%s%s", obj, detail);
	return (false);
}

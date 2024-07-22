/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 08:42:04 by ael-mank          #+#    #+#             */
/*   Updated: 2024/07/22 13:41:37 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int main(void)
{
	t_mlx	mlx;

	if (!(mlx.mlx_ptr = mlx_init()))
		exit(EXIT_FAILURE);
	if (!(mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, 960, 540, "MiniRT")))
		exit(EXIT_FAILURE);
	mlx_key_hook(mlx.win_ptr, keys_handler, &mlx);
	mlx_hook(mlx.win_ptr, 17, 0, ft_exit, &mlx);
	mlx_loop(mlx.mlx_ptr);
}
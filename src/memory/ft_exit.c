/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 08:57:27 by ael-mank          #+#    #+#             */
/*   Updated: 2024/08/07 10:46:13 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	ft_exit(t_mlx *mlx)
{
	mlx_destroy_image(mlx->mlx_ptr, mlx->img.img);
	//first destroy images if used with mlx_destroy_image
	//then destroy window
	mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
	//destroy display
	mlx_destroy_display(mlx->mlx_ptr);
	free(mlx->mlx_ptr);
	printf("\033[1;32mGame Closed by User.\033[0m\n");
	exit(0);
}
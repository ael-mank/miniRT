/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_inputs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 08:55:32 by ael-mank          #+#    #+#             */
/*   Updated: 2024/07/22 13:41:45 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	keys_handler(int key_code, t_mlx *mlx)
{
	//show pressed key, has to be removed
	//ft_printf("Key pressed: %d\n", key_code);
	if (key_code == XK_Escape)
		ft_exit(mlx);
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_inputs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 08:55:32 by ael-mank          #+#    #+#             */
/*   Updated: 2024/08/19 09:13:51 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	keys_handler(int key_code, t_scene *scene)
{
	if (key_code == XK_Escape)
		ft_exit(scene);
	return (0);
}

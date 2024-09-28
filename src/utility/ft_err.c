/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_err.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 09:52:55 by ael-mank          #+#    #+#             */
/*   Updated: 2024/09/28 20:36:36 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_error(t_scene *scene, char *msg)
{
	ft_printf("\e[1;31mError :");
	ft_printf("\t%s\n\033[0m", msg);
	scene->bvh = create_bvh_node(scene->objects);
	ft_exit(scene);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_comp2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 20:58:04 by ael-mank          #+#    #+#             */
/*   Updated: 2024/08/20 21:44:54 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	compare_objects_x(const void *a, const void *b)
{
	return (box_x_compare(a, b));
}

int	compare_objects_y(const void *a, const void *b)
{
	return (box_y_compare(a, b));
}

int	compare_objects_z(const void *a, const void *b)
{
	return (box_z_compare(a, b));
}

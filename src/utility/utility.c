/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 11:40:42 by ael-mank          #+#    #+#             */
/*   Updated: 2024/08/10 13:48:35 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

double 	deg_to_rad(double degrees)
{
	return (degrees * M_PI / 180);
}

double rand_double(double min, double max)
{
	return (min + (max - min) * random_double());
}

double random_double(void)
{
	return (rand() / (RAND_MAX + 1.0));
}
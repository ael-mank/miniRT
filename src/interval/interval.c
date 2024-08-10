/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interval.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 13:04:34 by ael-mank          #+#    #+#             */
/*   Updated: 2024/08/10 14:19:59 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double size(t_interval interval)
{
	return (interval.max - interval.min);
}

int contains(t_interval interval, double x)
{
	return (x >= interval.min && x <= interval.max);
}

int surrond(t_interval a, t_interval b)
{
	return (a.min <= b.min && a.max >= b.max);
}

// Function to clamp a value within the interval
double clamp(double x, double min, double max) {
    if (x < min)
        return (min);
    if (x > max)
        return (max);
    return (x);
}
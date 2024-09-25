/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interval.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 13:02:07 by ael-mank          #+#    #+#             */
/*   Updated: 2024/09/25 10:02:53 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERVAL_H
# define INTERVAL_H

# include "minirt.h"

/* Structure representing an interval with a minimum and maximum value */
typedef struct s_interval
{
	double	min;
	double	max;
}			t_interval;

/* Create an interval with specified min and max values */
t_interval	interval(double min, double max);

/* Get the size (length) of the interval */
double		size(t_interval interval);

/* Check if the interval contains a specific value x */
int			contains(t_interval interval, double x);

/* Clamp a value 'x' between 'min' and 'max' */
double		clamp(double x, double min, double max);

/* Interval Getters*/
t_interval	universe_interval(void);
t_interval	infinite_interval(void);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interval.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 13:02:07 by ael-mank          #+#    #+#             */
/*   Updated: 2024/09/24 15:39:31 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERVAL_H
# define INTERVAL_H

# include "minirt.h"

# define empty_interval \
	(t_interval)       \
	{                  \
		0, 0           \
	}

# define universe_interval \
	(t_interval)          \
	{                     \
		0.001, INFINITY   \
	}

# define infinite_interval   \
	(t_interval)            \
	{                       \
		-INFINITY, INFINITY \
	}

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

#endif
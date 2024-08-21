/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interval.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 13:02:07 by ael-mank          #+#    #+#             */
/*   Updated: 2024/08/21 10:41:25 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERVAL_H
# define INTERVAL_H

# include "minirt.h"

/* Define an empty interval with min and max set to 0 */
# define empty_interval (t_interval){0, 0}

/* Define a universe interval with min set to 0.001 and max set to infinity */
# define universe_interval (t_interval){0.001, INFINITY}

typedef struct s_interval
{
    double	min;
    double	max;
}				t_interval;

t_interval	interval(double min, double max);

double size(t_interval interval);

int contains(t_interval interval, double x);

/* Function to check if interval 'a' surrounds interval 'b' */
int surrond(t_interval a, t_interval b);

/* Function to clamp a value 'x' between 'min' and 'max' */
double clamp(double x, double min, double max);

#endif
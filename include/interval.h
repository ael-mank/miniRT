/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interval.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 13:02:07 by ael-mank          #+#    #+#             */
/*   Updated: 2024/08/10 18:10:20 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERVAL_H
# define INTERVAL_H

# include "minirt.h"

# define empty_interval (t_interval){0, 0}
# define universe_interval (t_interval){0.001, INFINITY}

typedef struct s_interval
{
	double	min;
	double	max;
}				t_interval;

double size(t_interval interval);

int contains(t_interval interval, double x);

int surrond(t_interval a, t_interval b);

double clamp(double x, double min, double max);

#endif
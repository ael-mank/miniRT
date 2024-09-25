/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_intervals.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 10:01:16 by ael-mank          #+#    #+#             */
/*   Updated: 2024/09/25 10:01:58 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_interval	infinite_interval(void)
{
	return ((t_interval){-INFINITY, INFINITY});
}

t_interval	universe_interval(void)
{
	return ((t_interval){0.001, INFINITY});
}

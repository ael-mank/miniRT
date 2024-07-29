/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 14:05:55 by ael-mank          #+#    #+#             */
/*   Updated: 2024/07/29 14:05:56 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
#define RAY_H

#include "vectors.h"

typedef struct {
    t_coord orig;
    t_coord dir;
} ray;

void ray_init(ray* r, const t_coord* origin, const t_coord* direction);
const t_coord* ray_origin(const ray* r);
const t_coord* ray_direction(const ray* r);
t_coord ray_at(const ray* r, double t);

#endif // RAY_H
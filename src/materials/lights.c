/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 15:02:21 by ael-mank          #+#    #+#             */
/*   Updated: 2024/09/06 16:28:18 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3 no_light(t_material *mat, t_hitrecord *rec)
{
    (void)mat;
    (void)rec;
    return vec3(0, 0, 0);
}

t_vec3 diffuse_light(t_material *mat, t_hitrecord *rec)
{
	(void)mat;
    (void)rec;
    return mat->texture(mat, rec);
}
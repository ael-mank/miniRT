/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mats.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 12:30:43 by ael-mank          #+#    #+#             */
/*   Updated: 2024/09/25 12:32:31 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATS_H
# define MATS_H

# include "minirt.h"

t_material	make_matte(void);
t_material	make_invisible(void);
t_material	make_light(void);
t_material	make_metal(void);
t_material	make_checkerboard(void);
t_material	make_globe(void);
t_material	make_glass(double ref_indx);

#endif
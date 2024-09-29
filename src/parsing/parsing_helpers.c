/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 09:25:08 by ael-mank          #+#    #+#             */
/*   Updated: 2024/09/29 09:26:20 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	get_val(int *color, char **line)
{
	while (ft_isspace(**line))
		(*line)++;
	if (!ft_isdigit(**line))
		return (0);
	*color = ft_atoi(*line);
	if (*color < 0 || *color > 255)
		return (0);
	while (ft_isdigit(**line))
		(*line)++;
	return (1);
}

int	get_color(int *r, int *g, int *b, char *line)
{
	if (!get_val(r, &line))
		return (0);
	if (*line != ',')
		return (0);
	line++;
	if (!get_val(g, &line))
		return (0);
	if (*line != ',')
		return (0);
	line++;
	if (!get_val(b, &line))
		return (0);
	return (1);
}

int	parse_vector(t_vec3 *vec, char **line)
{
	if (!parse_double(&vec->x, line))
		return (0);
	if (**line != ',')
		return (0);
	(*line)++;
	if (!parse_double(&vec->y, line))
		return (0);
	if (**line != ',')
		return (0);
	(*line)++;
	if (!parse_double(&vec->z, line))
		return (0);
	return (1);
}

int	parse_double(double *value, char **line)
{
	while (ft_isspace(**line))
		(*line)++;
	if (!ft_isdigit(**line) && **line != '-' && **line != '+')
		return (0);
	*value = ft_atof(*line);
	if (**line == '-' || **line == '+')
		(*line)++;
	while (ft_isdigit(**line) || **line == '.')
		(*line)++;
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_parameter.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrigny <yrigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 17:53:07 by yrigny            #+#    #+#             */
/*   Updated: 2024/09/24 19:48:54 by yrigny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	parse_ratio(char **line, double *ratio)
{
	char	*tmp;
	int		i;
	bool	res;

	while (*line && ft_isspace(**line))
		(*line)++;
	tmp = *line;
	if (*tmp == '\0')
		return (false);
	i = 0;
	while (tmp[i] && !ft_isspace(tmp[i]))
		i++;
	tmp = malloc(i + 1);
	ft_strlcpy(tmp, *line, i + 1);
	res = is_float_format(tmp);
	if (res == true)
	{
		*ratio = ft_atof(tmp);
		if (*ratio < 0.0 || *ratio > 1.0)
			res = false;
	}
	free(tmp);
	*line += i;
	return (res);
}

bool	parse_point(char **line, t_vec3 *point)
{
	char	*tmp;
	int		i;
	bool	res;

	while (**line && ft_isspace(**line))
		(*line)++;
	tmp = *line;
	if (*tmp == '\0')
		return (false);
	i = 0;
	while (tmp[i] && !ft_isspace(tmp[i]))
		i++;
	tmp = malloc(i + 1);
	ft_strlcpy(tmp, *line, i + 1);
	res = is_vec3_format(tmp, FLOAT);
	if (res == true)
		*point = ft_atovec3(tmp);
	free(tmp);
	*line += i;
	return (res);
}

bool	parse_color(char **line, t_color *color)
{
	char	*tmp;
	int		i;
	bool	res;

	while (**line && ft_isspace(**line))
		(*line)++;
	tmp = *line;
	if (*tmp == '\0')
		return (false);
	i = 0;
	while (tmp[i] && !ft_isspace(tmp[i]))
		i++;
	tmp = malloc(i + 1);
	ft_strlcpy(tmp, *line, i + 1);
	res = is_vec3_format(tmp, INTEGER);
	if (res == true)
	{
		*color = ft_atorgb(tmp);
		if (!(color->r >= 0 && color->r <= 255 && color->g >= 0
				&& color->g <= 255 && color->b >= 0 && color->b <= 255))
			res = false;
	}
	free(tmp);
	*line += i;
	return (res);
}

bool	parse_length(char **line, double *length)
{
	char	*tmp;
	bool	res;
	int		i;

	while (ft_isspace(**line))
		(*line)++;
	tmp = *line;
	if (*tmp == '\0')
		return (false);
	i = 0;
	while (tmp[i] && !ft_isspace(tmp[i]))
		i++;
	tmp = malloc(i + 1);
	ft_strlcpy(tmp, *line, i + 1);
	res = is_float_format(tmp);
	if (res == true)
	{
		*length = ft_atof(tmp);
		if (*length <= 0.0)
			res = false;
	}
	free(tmp);
	*line += i;
	return (res);
}

bool	parse_direction(char **line, t_vec3 *vec)
{
	char	*tmp;
	int		i;
	bool	res;

	while (**line && ft_isspace(**line))
		(*line)++;
	tmp = *line;
	if (*tmp == '\0')
		return (false);
	i = 0;
	while (tmp[i] && !ft_isspace(tmp[i]))
		i++;
	tmp = malloc(i + 1);
	ft_strlcpy(tmp, *line, i + 1);
	res = is_vec3_format(tmp, FLOAT);
	if (res == true)
	{
		*vec = ft_atovec3(tmp);
		if (!(vec->x >= -1 && vec->x <= 1 && vec->y >= -1 && vec->y <= 1
				&& vec->z >= -1 && vec->z <= 1 && vector_length(*vec) > 0))
			res = false;
	}
	free(tmp);
	*line += i;
	return (res);
}

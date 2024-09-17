/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_helper_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrigny <yrigny@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 19:03:27 by yrigny            #+#    #+#             */
/*   Updated: 2024/09/17 14:08:40 by yrigny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	is_float_format(char *s)
{
	int		nb_parts;
	char	**parts;
	bool	res;

	nb_parts = count_parts(s, '.');
	parts = NULL;
	if (nb_parts == 1 && str_is_int(s))
		res = true;
	else if (nb_parts == 2)
	{
		parts = ft_split(s, '.');
		if (str_is_int(parts[0]) && str_is_digit(parts[1]))
			res = true;
		else
			res = false;
		free(parts[0]);
		free(parts[1]);
		free(parts);
	}
	else
		res = false;
	return (res);
}

int		count_parts(char *s, char c)
{
	int		count;

	count = 0;
	if (!s)
		return (count);
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			count += 1;
		while (*s && *s != c)
			s++;
	}
	return (count);
}

bool	str_is_int(char *s)
{
	bool	is_signed;

	is_signed = false;
	if (s && *s == '-')
	{
		is_signed = true;
		s++;
	}
	if (*s == '\0' || !str_is_digit(s))
		return (false);
	if (is_signed && s[0] == '0')
		return (false);
	if (s && ft_strlen(s) > 1 && s[0] == '0')
		return (false);
	return (true);
}

bool	str_is_digit(char *s)
{
	if (!s)
		return (false);
	while (*s)
	{
		if (!(*s >= '0' && *s <= '9'))
			return (false);
		s++;
	}
	return (true);
}

double	ft_atof(char *s)
{
	char	*no_dot;
	int		significant;
	int		i;
	int		e;
	double	res;

	no_dot = malloc(ft_strlen(s));
	i = -1;
	e = 0;
	while (s[++i] != '.')
		no_dot[i] = s[i];
	if (s[i] == '.')
	{
		i += 1;
		while (s[i + e])
		{
			no_dot[i - 1 + e] = s[i + e];
			e++;
		}
	}
	no_dot[i + e] = '\0';
	significant = ft_atoi(no_dot);
	free(no_dot);
	res = significant / pow(10, e);
	return (res);
}

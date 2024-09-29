/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_type.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 09:34:47 by ael-mank          #+#    #+#             */
/*   Updated: 2024/09/29 09:44:07 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	get_string(char *line, char **str)
{
	int		i;
	char	*start;

	i = 0;
	start = line;
	while (*line && !ft_isspace(*line))
	{
		line++;
		i++;
	}
	*str = malloc(sizeof(char) * (i + 1));
	if (!*str)
		return ;
	line = start;
	i = 0;
	while (*line && !ft_isspace(*line))
	{
		(*str)[i] = *line;
		i++;
		line++;
	}
	(*str)[i] = '\0';
}

t_material_type	get_type(char *line)
{
	if (!ft_strncmp(line, "matte", 5))
		return (free(line), MATTE);
	else if (!ft_strncmp(line, "metal", 5))
		return (free(line), METAL);
	else if (!ft_strncmp(line, "glass", 5))
		return (free(line), GLASS);
	else if (!ft_strncmp(line, "globe", 6))
		return (free(line), GLOBE);
	else if (!ft_strncmp(line, "light", 5))
		return (free(line), LIGHT);
	else if (!ft_strncmp(line, "checkerboard", 13))
		return (free(line), CHECKERBOARD);
	else
	{
		if (line[0] != '\0')
		{
			ft_printf("\e[1;31mError :");
			ft_printf("\t%s\n\033[0m",
				"Unrecognized material type replaced by matte");
		}
		return (free(line), MATTE);
	}
}

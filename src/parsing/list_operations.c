/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 09:24:49 by ael-mank          #+#    #+#             */
/*   Updated: 2024/09/29 09:46:30 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	fill_lst(t_scene *scene)
{
	char	*line;
	int		empty;

	empty = 1;
	while (1)
	{
		line = get_next_line(scene->file_fd);
		if (line == NULL)
			break ;
		if (*line == '\0')
		{
			free(line);
			continue ;
		}
		if (scene->lst_map == NULL)
			scene->lst_map = ft_lstnew(line);
		else
			ft_lstadd_back(&scene->lst_map, ft_lstnew(line));
		empty = 0;
	}
	if (empty)
		return (0);
	return (1);
}

int	parse_lst(t_scene *scene)
{
	t_list	*tmp;
	char	*line;

	tmp = scene->lst_map;
	while (tmp)
	{
		line = tmp->content;
		while (ft_isspace(*line))
			line++;
		if (!check_char(scene, line) && *line != '\n' && *line != '\0')
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

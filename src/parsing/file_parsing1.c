/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parsing1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 09:51:52 by ael-mank          #+#    #+#             */
/*   Updated: 2024/09/28 20:47:23 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	open_map(t_scene *scene, char *path)
{
	int	path_len;

	path_len = ft_strlen(path);
	if (path_len < 3)
		return (0);
	if (ft_strncmp(&path[path_len - 3], ".rt", ft_strlen(&path[path_len
				- 4])) != 0)
		return (0);
	scene->file_fd = open(path, O_RDONLY);
	if (scene->file_fd < 0)
		return (0);
	return (1);
}

int	fill_lst(t_scene *scene)
{
	char	*line;
	int		empty;

	empty = 1;
	while ((line = get_next_line(scene->file_fd)) != NULL)
	{
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

int	check_char(t_scene *scene, char *line)
{
	if (*line == 'A' || *line == 'a')
		return (parse_ambient(scene, line));
	else if (*line == 'c' && *(line + 1) == 'y')
		return (parse_cylinder(scene, line));
	else if (*line == 'C' || *line == 'c')
		return (parse_camera(scene, line));
	else if (*line == 'L' || *line == 'l')
		return (parse_light(scene, line));
	else if (*line == 's' && *(line + 1) == 'p')
		return (parse_sphere(scene, line));
	else if (*line == 'p' && *(line + 1) == 'l')
		return (parse_plane(scene, line));
	// else if (*line == 't' && *(line + 1) == 'r')
	// 	//return(parse_triangle(scene, line));
	else if (*line == '#')
		return (1);
	else
		return (0);
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
		//printf("line: %s\n", line);
		if (!check_char(scene, line) && *line != '\n' && *line != '\0')
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

void	print_lst(t_scene *scene)
{
	t_list	*tmp;

	tmp = scene->lst_map;
	while (tmp)
	{
		ft_printf("%s\n", tmp->content);
		tmp = tmp->next;
	}
}

void	parse_file(t_scene *scene, char **argv)
{
	scene->c_and_a = 0;
	if (!open_map(scene, argv[1]))
		ft_error(scene, "Unable to open scene file.");
	if (!fill_lst(scene))
		ft_error(scene, "Empty File.");
	if (!parse_lst(scene))
		ft_error(scene, "Parsing error.");
	if (scene->c_and_a != 2)
		ft_error(scene, "No ambient or camera.");
}
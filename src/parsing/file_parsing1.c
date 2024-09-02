/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parsing1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 09:51:52 by ael-mank          #+#    #+#             */
/*   Updated: 2024/09/02 15:22:27 by ael-mank         ###   ########.fr       */
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

int set_vars(t_scene *scene)
{
	//TODO
	//USE GNL PARSE FILE FIND THE TOKENS (S SPHERE T TRIANGLE B BOX L LIGHT C CAMERA)
	//USE FUNCTION TO SET/CREATE THE THING NEEDDED
	(void)scene;
	return (1);
}


void parse_file(t_scene *scene, char **argv)
{
	if (!open_map(scene, argv[1]))
		ft_error(scene, "Unable to open scene file.");
	if (!set_vars(scene))
		ft_error(scene, "Invalid scene.");
}
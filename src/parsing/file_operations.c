/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 09:24:30 by ael-mank          #+#    #+#             */
/*   Updated: 2024/09/29 09:26:26 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	open_map(t_scene *scene, char *path)
{
	int	path_len;

	path_len = ft_strlen(path);
	if (path_len < 3)
		return (0);
	if (ft_strncmp(&path[path_len - 3], ".rt", 3) != 0)
		return (0);
	scene->file_fd = open(path, O_RDONLY);
	if (scene->file_fd < 0)
		return (0);
	return (1);
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

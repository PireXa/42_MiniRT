/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MINIRT                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdas-nev <rdas-nev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 4242/42/42 42:42:42 by rdas-nev          #+#    #+#             */
/*   Updated: 4242/42/42 42:42:42 by rdas-nev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

int	triangle_counter(char *file)
{
	int		fd;
	int		count;
	char	*line;

	count = 0;
	fd = open(file, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		if (line[0] == 't' && line[1] == 'r')
			count++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	return (count);
}

int	camera_counter(char *file)
{
	int		fd;
	int		count;
	char	*line;

	count = 0;
	fd = open(file, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		if (line[0] == 'C' && (line[1] == ' ' || line[1] == '\t'))
			count++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	return (count);
}

int	light_counter(char *file)
{
	int		fd;
	int		count;
	char	*line;

	count = 0;
	fd = open(file, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		if (line[0] == 'L' && (line[1] == ' ' || line[1] == '\t'))
			count++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	return (count);
}

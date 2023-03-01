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

int	sphere_counter(char *file)
{
	int		fd;
	int		count;
	char	*line;

	count = 0;
	fd = open(file, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		if (line[0] == 's' && line[1] == 'p')
			count++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	return (count);
}

int	plane_counter(char *file)
{
	int		fd;
	int		count;
	char	*line;

	count = 0;
	fd = open(file, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		if (line[0] == 'p' && line[1] == 'l')
			count++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	return (count);
}

int	cylinder_counter(char *file)
{
	int		fd;
	int		count;
	char	*line;

	count = 0;
	fd = open(file, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		if (line[0] == 'c' && line[1] == 'y')
			count++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	return (count);
}

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

int	rgb_to_int(int r, int g, int b)
{
	if (r > 255)
		exit(printf("\033[31mError\nRed value too high\033[0m\n"));
	if (g > 255)
		exit(printf("\033[31mError\nGreen value too high\033[0m\n"));
	if (b > 255)
		exit(printf("\033[31mError\nBlue value too high\033[0m\n"));
	return (r << 16 | g << 8 | b);
}

void	free_double_array(char **array)
{
	int	i;

	i = -1;
	if (!array)
		return ;
	while (array[++i])
		free(array[i]);
	free(array);
}

void	get_to_eof(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
	free(line);
}

float	get_material_data(char *mat_ref, int data)
{
	int		fd;
	char	*fds;
	char	**split;
	float	ret;

	fd = open("./materials/materials_data", O_RDONLY);
	fds = get_next_line(fd);
	while (ft_strncmp(fds, mat_ref, ft_strlen(mat_ref) - 1))
	{
		free(fds);
		fds = get_next_line(fd);
	}
	split = tab_space_split(fds);
	ret = ft_atof(split[data]);
	free_double_array(split);
	free(fds);
	get_to_eof(fd);
	close(fd);
	return (ret);
}

int	double_array_len(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return (0);
	while (array[i])
		i++;
	return (i);
}

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

#include"../../inc/minirt.h"

void	free_matrix(float **array, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_view_matrix(t_camera *cameras, int nb_cameras)
{
	int	i;

	i = 0;
	while (i < nb_cameras)
	{
		free_matrix(cameras[i].view_matrix, 4);
		i++;
	}
}

void	reach_eof(int fd, t_data *data)
{
	while (data->line)
	{
		free(data->line);
		data->line = get_next_line(fd);
	}
}

int	free_all(t_data *data, int exit_code)
{
	mlx_destroy_image(data->mlx, data->img.img);
	if (data->mlx_win)
		mlx_destroy_window(data->mlx, data->mlx_win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	free(data->scene->spheres);
	free(data->scene->planes);
	free(data->scene->cylinders);
	if (data->scene->cameras[0].fov != -1)
		free_view_matrix(data->scene->cameras, data->nb_objs->nb_cameras);
	free(data->scene->cameras);
	free(data->scene->amb_light);
	free(data->scene->lights);
	free(data->scene->triangles);
	free(data->scene);
	free(data->nb_objs);
	if (data->params)
		free_double_array(data->params);
	if (data->line)
		reach_eof(data->fd, data);
	close(data->fd);
	free(data);
	exit(exit_code);
}

#include"../../inc/minirt.h"

void free_matrix(float **array, int size)
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

int	free_all(t_data *data)
{
	mlx_destroy_window(data->mlx, data->mlx_win);
	free(data->nb_objs);
	free_view_matrix(data->scene->cameras, data->nb_objs->nb_cameras);
	free(data->scene->spheres);
	free(data->scene->planes);
	free(data->scene->cylinders);
	free(data->scene->cameras);
	free(data->scene->amb_light);
	free(data->scene);
	free(data);
	exit(0);
}

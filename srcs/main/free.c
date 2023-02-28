#include"../../inc/minirt.h"

int	free_all(t_data *data)
{
	mlx_destroy_window(data->mlx, data->mlx_win);
	free(data->nb_objs);
	free(data->scene->spheres);
	free(data->scene->planes);
	free(data->scene->cylinders);
	free(data->scene->cameras);
	free(data->scene->amb_light);
	free(data->scene);
	free(data);
	exit(0);
}

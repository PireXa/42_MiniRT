#include "../../inc/minirt.h"

long int	current_time_millis()
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	light_animation(t_data *data)
{
	long int	current_time;

	current_time = current_time_millis();
	if (data->animation.time < current_time)
	{
		ray_tracer(data);
		data->animation.time = current_time + 10;
		data->scene->cameras[0].normal.x += 0.1;
		/*data->light->origin.x += 1;
		data->light->origin.y = sin(data->light->origin.x / 70);*/
	}
}

int render(t_data *data)
{
	light_animation(data);
	ray_tracer(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.img, 0, 0);
	fps(data);
	return (0);
}

void	init_graphics(t_data *data)
{
	data->mlx_win = mlx_new_window(data->mlx, WIND_W, WIND_H, "MiniRT");
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.img, 0, 0);
}

void	loop(t_data *data)
{
	ray_tracer(data);
	init_graphics(data);
	controls(data);
	printf("Render time: %ld ms\n", current_time_millis() - data->start_render_time);
	//mlx_loop_hook(data->mlx, render, data);
	mlx_loop(data->mlx);
}

int main(int argc, char **argv)
{
	t_data		*data;
	t_ray		ray;

	if (argc != 2)
	{
		printf("Correct usage: ./minirt (scene.rt)\n");
		return (0);
	}
	data = (t_data *)malloc(sizeof(t_data));
	init_data(data, argv[1]);
	printf("Parsing scene...\n");
	parser(argv[1], data->scene);
	printf("Rendering...\n");
	loop(data);
}

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
		data->light->origin.x += 30;
		data->light->origin.y = sin(data->light->origin.x / 70) * 300 + 300;
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

void	loop(t_data *data)
{
	controls(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.img, 0, 0);
	printf("Render time: %ld ms\n", current_time_millis() - data->start_render_time);
	//	mlx_loop_hook(data->mlx, render, data);
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
	data->mlx = mlx_init();
	data->mlx_win = mlx_new_window(data->mlx, WIND_W, WIND_H, "MiniRT");
	data->img.img = mlx_new_image(data->mlx, WIND_W, WIND_H);
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bi_per_pxl, &data->img.line_length, &data->img.endian);
	data->nb_objs = malloc(sizeof(t_nb_objs));
	data->nb_objs->nb_spheres = sphere_counter(argv[1]);
	data->nb_objs->nb_planes = plane_counter(argv[1]);
	data->nb_objs->nb_cylinders = cylinder_counter(argv[1]);
	data->nb_objs->nb_triangles = triangle_counter(argv[1]);
	data->scene = (t_scene *)malloc(sizeof(t_scene));
	data->scene->spheres = (t_sphere *)malloc(sizeof(t_sphere) * data->nb_objs->nb_spheres);
	data->scene->planes = (t_plane *)malloc(sizeof(t_plane) * data->nb_objs->nb_planes);
	data->scene->cylinders = (t_cylinder *)malloc(sizeof(t_cylinder) * data->nb_objs->nb_cylinders);
	data->scene->triangles = (t_triangle *)malloc(sizeof(t_triangle) * data->nb_objs->nb_triangles);
	printf("Parsing scene...\n");
	parser(argv[1], data->scene);
	data->camera.x = (WIND_W / 2);
	data->camera.y = (WIND_H / 2) - 200;
	data->camera.z = -1000;
	data->light = malloc(sizeof(t_light));
	data->light->origin.x = 600;
	data->light->origin.y = 600;
	data->light->origin.z = 100;
	data->light->intensity = 1;
	data->light->color = 0xFFFFFF;
	data->fps.frame_time = time(NULL);
	data->fps.frame_ctr = 0;
	data->fps.fps = 0;
	data->start_render_time = current_time_millis();
	printf("Rendering...\n");
	ray_tracer(data);
	loop(data);
}

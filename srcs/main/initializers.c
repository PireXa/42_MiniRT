#include "../../inc/minirt.h"

void	init_data(t_data *data, char *scene_file)
{
	data->mlx = mlx_init();
	data->img.img = mlx_new_image(data->mlx, WIND_W, WIND_H);
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bi_per_pxl, &data->img.line_length, &data->img.endian);
	data->nb_objs = malloc(sizeof(t_nb_objs));
	data->nb_objs->nb_spheres = sphere_counter(scene_file);
	data->nb_objs->nb_planes = plane_counter(scene_file);
	data->nb_objs->nb_cylinders = cylinder_counter(scene_file);
	data->nb_objs->nb_triangles = triangle_counter(scene_file);
	data->scene = (t_scene *)malloc(sizeof(t_scene));
	data->scene->spheres = (t_sphere *)malloc(sizeof(t_sphere) * data->nb_objs->nb_spheres);
	data->scene->planes = (t_plane *)malloc(sizeof(t_plane) * data->nb_objs->nb_planes);
	data->scene->cylinders = (t_cylinder *)malloc(sizeof(t_cylinder) * data->nb_objs->nb_cylinders);
	data->scene->triangles = (t_triangle *)malloc(sizeof(t_triangle) * data->nb_objs->nb_triangles);
	data->camera.x = (WIND_W / 2);
	data->camera.y = -1000;
	data->camera.z = (WIND_H / 2) + 200;
	data->light = malloc(sizeof(t_light));
	data->light->origin.x = 600;
	data->light->origin.y = 100;
	data->light->origin.z = 600;
	data->light->intensity = 1;
	data->light->color = 0xFFFFFF;
	data->fps.frame_time = time(NULL);
	data->fps.frame_ctr = 0;
	data->fps.fps = 0;
	data->start_render_time = current_time_millis();
}

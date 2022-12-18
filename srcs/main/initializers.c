#include "../../inc/minirt.h"

float	**set_camera_to_world_transformation_matrix(t_camera camera, t_vector up)
{
	float	**matrix;
	t_vector	z_axis;
	t_vector	x_axis;
	t_vector	y_axis;

	matrix = malloc(sizeof(float *) * 4);
	matrix[0] = malloc(sizeof(float) * 4);
	matrix[1] = malloc(sizeof(float) * 4);
	matrix[2] = malloc(sizeof(float) * 4);
	matrix[3] = malloc(sizeof(float) * 4);
//	z_axis = vector_sub(camera.origin, camera.normal);
	z_axis.x = camera.normal.x;
	z_axis.y = camera.normal.y;
	z_axis.z = -camera.normal.z;
	normalize_vector(&z_axis);
	x_axis = cross_product(up, z_axis);
	normalize_vector(&x_axis);
	y_axis = cross_product(z_axis, x_axis);
	normalize_vector(&y_axis);
	matrix[0][0] = x_axis.x;
	matrix[0][1] = x_axis.y;
	matrix[0][2] = x_axis.z;
	matrix[0][3] = 0;//-dot_product(x_axis, camera.origin);
	matrix[1][0] = y_axis.x;
	matrix[1][1] = y_axis.y;
	matrix[1][2] = y_axis.z;
	matrix[1][3] = 0;//-dot_product(y_axis, camera.origin);
	matrix[2][0] = z_axis.x;
	matrix[2][1] = z_axis.y;
	matrix[2][2] = z_axis.z;
	matrix[2][3] = 0;//-dot_product(z_axis, camera.origin);
	matrix[3][0] = camera.origin.x;
	matrix[3][1] = camera.origin.y;
	matrix[3][2] = -camera.origin.z;
	matrix[3][3] = 1;
	return (matrix);
}

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
	data->scene->cameras = (t_camera *)malloc(sizeof(t_camera) * 1);
	data->scene->cameras[0].origin = (t_vector){0, 1.5, 0};
	data->scene->cameras[0].normal = (t_vector){0, 0, 1};
	normalize_vector(&data->scene->cameras[0].normal);
//	data->scene->cameras[0].view_matrix = set_camera_to_world_transformation_matrix(data->scene->cameras[0]);
	data->scene->cameras[0].view_matrix = set_camera_to_world_transformation_matrix(data->scene->cameras[0], (t_vector){0, 1, 0});
	data->light = malloc(sizeof(t_light));
	data->light->origin.x = 0;
	data->light->origin.y = 3.6;
	data->light->origin.z = 4.5;
	data->light->intensity = 1;
	data->light->color = 0xFFFFFF;
	data->fps.frame_time = time(NULL);
	data->fps.frame_ctr = 0;
	data->fps.fps = 0;
	data->start_render_time = current_time_millis();
}

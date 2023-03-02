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

float	*init_mtrx(float *values, float *matrix)
{
	matrix[0] = values[0];
	matrix[1] = values[1];
	matrix[2] = values[2];
	matrix[3] = values[3];
	return (matrix);
}

float	**set_cam_wrld_mtrx(t_camera c, t_vector up)
{
	float		**m;
	t_vector	z_axis;
	t_vector	x_axis;
	t_vector	y_axis;

	m = malloc(sizeof(float *) * 4);
	m[0] = malloc(sizeof(float) * 4);
	m[1] = malloc(sizeof(float) * 4);
	m[2] = malloc(sizeof(float) * 4);
	m[3] = malloc(sizeof(float) * 4);
	z_axis.x = c.normal.x;
	z_axis.y = c.normal.y;
	z_axis.z = c.normal.z;
	normalize_vector(&z_axis);
	x_axis = cross_product(up, z_axis);
	normalize_vector(&x_axis);
	y_axis = cross_product(z_axis, x_axis);
	normalize_vector(&y_axis);
	m[0] = init_mtrx((float [4]){x_axis.x, x_axis.y, x_axis.z, 0}, m[0]);
	m[1] = init_mtrx((float [4]){y_axis.x, y_axis.y, y_axis.z, 0}, m[1]);
	m[2] = init_mtrx((float [4]){z_axis.x, z_axis.y, z_axis.z, 0}, m[2]);
	m[3] = init_mtrx((float [4]){c.origin.x, c.origin.y, c.origin.z, 1}, m[3]);
	return (m);
}

void	mlx_data_init(t_data *d)
{
	d->mlx = mlx_init();
	d->img.img = mlx_new_image(d->mlx, WIND_W, WIND_H);
	d->img.addr = mlx_get_data_addr(d->img.img,
			&d->img.bi_per_pxl,
			&d->img.line_length, &d->img.endian);
}

void	nb_objs_init(t_data *data, char *scene_file)
{
	data->nb_objs = malloc(sizeof(t_nb_objs));
	data->nb_objs->nb_spheres = sphere_counter(scene_file);
	data->nb_objs->nb_planes = plane_counter(scene_file);
	data->nb_objs->nb_cylinders = cylinder_counter(scene_file);
	data->nb_objs->nb_triangles = triangle_counter(scene_file);
	data->nb_objs->nb_cameras = camera_counter(scene_file);
	data->nb_objs->nb_lights = light_counter(scene_file);
}

void	init_data(t_data *data, char *scene_file)
{
	mlx_data_init(data);
	nb_objs_init(data, scene_file);
	data->scene = (t_scene *)malloc(sizeof(t_scene));
	data->scene->spheres = (t_sphere *)malloc(sizeof(t_sphere)
			* data->nb_objs->nb_spheres);
	data->scene->planes = (t_plane *)malloc(sizeof(t_plane)
			* data->nb_objs->nb_planes);
	data->scene->cylinders = (t_cylinder *)malloc(sizeof(t_cylinder)
			* data->nb_objs->nb_cylinders);
	data->scene->triangles = (t_triangle *)malloc(sizeof(t_triangle)
			* data->nb_objs->nb_triangles);
	data->scene->cameras = (t_camera *)malloc(sizeof(t_camera)
			* data->nb_objs->nb_cameras);
	data->scene->cameras[0].fov = -1;
	data->scene->lights = (t_light *)malloc(sizeof(t_light)
			* data->nb_objs->nb_lights);
	data->scene->amb_light = (t_ambience *)malloc(sizeof(t_ambience));
	data->fps.frame_time = time(NULL);
	data->fps.frame_ctr = 0;
	data->fps.fps = 0;
	data->start_render_time = current_time_millis();
	data->edit_mode = 0;
	data->camera_index = 0;
	data->normal_mode = 0;
}

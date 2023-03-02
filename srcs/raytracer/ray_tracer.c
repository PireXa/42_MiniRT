/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-albe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 10:05:30 by fde-albe          #+#    #+#             */
/*   Updated: 2023/03/01 12:17:33 by fde-albe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

typedef struct s_thr_res
{
	int		x;
	int		y;
}				t_thr_res;

float	deg_to_rad(float degrees)
{
	return (degrees * M_PI / 180.00f);
}

t_ray	get_ray(t_data *data, int x, int y)
{
	float		aspect_ratio;
	t_vector	camera;
	t_ray		ray;

	aspect_ratio = WIND_W / WIND_H;
	camera.x = -(2 * (x + 0.5) / WIND_W - 1) * aspect_ratio
		* tanf(deg_to_rad(data->scene->cameras[data->camera_index].fov) / 2);
	camera.y = (1 - 2 * (y + 0.5) / WIND_H)
		* tanf(deg_to_rad(data->scene->cameras[data->camera_index].fov) / 2);
	camera.z = 1;
	normalize_vector(&camera);
	ray.origin = data->scene->cameras[data->camera_index].origin;
	ray.direction = transform_vector(camera,
			data->scene->cameras[data->camera_index].view_matrix);
	normalize_vector(&ray.direction);
	return (ray);
}

int	get_normal_color(t_hit_obj hit)
{
	int	r;
	int	g;
	int	b;

	r = (int)(((hit.normal.x + 1) / 2) * 255);
	g = (int)(((hit.normal.y + 1) / 2) * 255);
	b = (int)(((hit.normal.z + 1) / 2) * 255);
	return ((r << 16) | (g << 8) | b);
}

int	hit_color(t_data *data, t_ray ray, t_hit_obj hit)
{
	int			color;
	t_ref_cap	ref_cap;

	if (data->normal_mode)
		color = get_normal_color(hit);
	else
	{
		ref_cap.depth = REFLECTION_DEPTH;
		ref_cap.light_int = 1.0f;
		hit.color = reflection_refraction(data, ray, hit, ref_cap);
		color = shading(hit, ray, data);
		color = blend_colors(color, hit.color, hit.light_absorb_distance);
	}
	return (color);
}

void	ray_tracer(t_threads *tdata)
{
	int			color;
	t_ray		ray;
	t_hit_obj	hit;
	t_thr_res	res;

	res.x = tdata->x_min;
	res.y = 0;
	while (res.x < tdata->x_max)
	{
		while (res.y < (int)WIND_H)
		{
			ray = get_ray(tdata->data, res.x, res.y);
			hit = get_closest_intersection(tdata->data, ray);
			if (hit.t_min < 4535320)
				color = hit_color(tdata->data, ray, hit);
			else
				color = background_color(res.y, BACKGROUND1, BACKGROUND2);
			put_pxl(&tdata->data->img, res.x, res.y, color);
			res.y++;
		}
		res.y = 0;
		tdata->x++;
		res.x++;
	}
}

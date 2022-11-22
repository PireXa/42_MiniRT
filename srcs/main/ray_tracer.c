#include "../../inc/minirt.h"

void	light_animation(t_data *data)
{
	if (data->animation.time < time(NULL))
	{
		data->animation.time = time(NULL);
		data->light->origin.x += 100;
	}
}

float	intersect_ray_sphere(t_ray ray, t_sphere sphere)
{
	t_vector oc;
	float a;
	float b;
	float c;
	float discriminant;
	float t;

	oc = vector_from_points(sphere.center, ray.origin);
	a = dot_product(ray.direction, ray.direction);
	b = 2.0 * dot_product(oc, ray.direction);
	c = dot_product(oc, oc) - sphere.radius * sphere.radius;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (0);
	t = (-b - sqrt(discriminant)) / (2.0 * a);
	if (t > 0.0001f)
		return (t);
	t = (-b + sqrt(discriminant)) / (2.0 * a);
	if (t > 0.0001f)
		return (t);
	return (0);
}

float intersect_ray_plane(t_ray ray, t_plane plane, t_vector screen)
{
	float t;
	float denom;
	t_vector p0l0;

	denom = dot_product(plane.normal, ray.direction);
	if (fabs(denom) > 0.0001f)
	{
		p0l0 = vector_from_points(ray.origin, plane.point);//, ray.origin);
		t = dot_product(p0l0, plane.normal) / denom;
		if (t > 0.0001f)
			return (t);
	}
	return (0);
}

void	ray_tracer(t_data *data)
{
	t_ray ray;
	t_vector	screen;
	int x;
	int y;
	int color;
	int i;
	float t;
	float t_min;
	int 	closest_sphere;
	int 	closest_plane;

	x = 0;
	y = 0;
	i = -1;
	t_min = 4535320;
	closest_sphere = -1;
	closest_plane = -1;
	while (x < (int)WIND_W)
	{
		while (y < (int)WIND_H)
		{
			screen.x = (float)x;
			screen.y = (float)y;
			screen.z = 0;
			ray.origin = data->camera;
			ray.direction = vector_from_points(data->camera, screen);
			normalize_vector(&ray.direction);
			while(++i < data->nb_objs->nb_spheres)
			{
				t = intersect_ray_sphere(ray, data->scene->spheres[i]);
				if (t)
				{
					if (t < t_min)
					{
						t_min = t;
						closest_sphere = i;
					}
				}
			}
			i = -1;
			while(++i < data->nb_objs->nb_planes)
			{
				t = intersect_ray_plane(ray, data->scene->planes[i], screen);
				if (t)
				{
					if (t < t_min)
					{
						t_min = t;
						closest_plane = i;
					}
				}
			}
			if (closest_sphere != -1)
			{
				color = shading_sphere(data->scene->spheres[closest_sphere], ray, t_min, data->light[0]);
				closest_sphere = -1;
				t_min = 4535320;
			}
			else if (closest_plane != -1)
			{
				if (!check_shadow(data, ray, t_min, data->light[0]))
					color = calc_color_intensity(data->scene->planes[closest_plane].color, light_intens_by_dist(data->light[0], data->scene->planes[closest_plane], ray, t_min));
				else
					color = calc_color_intensity(data->scene->planes[closest_plane].color, 0.1);
				closest_plane = -1;
				t_min = 4535320;
			}
			else
				color = background_color(y, BACKGROUND1, BACKGROUND2);
			i = -1;
			put_pxl(&data->img, x, y, color);
			y++;
		}
		y = 0;
		x++;
	}
}

int render(t_data *data)
{
	//light_animation(data);
	ray_tracer(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.img, 0, 0);
	fps(data);
	return (0);
}

void	loop(t_data *data)
{
	controls(data);
	mlx_loop_hook(data->mlx, render, data);
	mlx_loop(data->mlx);
}

int main(int argc, char **argv)
{
	t_data		*data;
	t_ray		ray;

	if (argc != 2)
	{
		printf("Give me a sphere radius\n");
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
	data->scene = (t_scene *)malloc(sizeof(t_scene));
	data->scene->spheres = (t_sphere *)malloc(sizeof(t_sphere) * data->nb_objs->nb_spheres);
	data->scene->planes = (t_plane *)malloc(sizeof(t_plane) * data->nb_objs->nb_planes);
	parser(argv[1], data->scene);
	data->camera.x = (WIND_W / 2);
	data->camera.y = (WIND_H / 2) - 200;
	data->camera.z = -1000;
	data->light = malloc(sizeof(t_light));
	data->light->origin.x = 500;
	data->light->origin.y = 100;
	data->light->origin.z = -100;
	data->light->intensity = 1;
	data->light->color = 0xFFFFFF;
	data->fps.frame_time = time(NULL);
	data->fps.frame_ctr = 0;
	data->fps.fps = 0;
	loop(data);
}

// Path: srcs/ray_tracer.c
// Compare this snippet from srcs/main.c:
// #include "../inc/minirt.h"
//
// int render(t_data *data)
// {
// 	int x;
// 	int y;
//
// 	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.img, 0, 0);
// 	mlx_destroy_image(data->mlx, data->img.img);
//
// 	return (0);
// }
//
// void	loop(t_data *data)
// {
// 	controls(data);
// 	mlx_loop_hook(data->mlx, render, data);
// 	mlx_loop(data->mlx);
// }
//
// int main(int ac, char **av)
// {




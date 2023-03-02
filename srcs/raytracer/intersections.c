/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-albe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 10:05:30 by fde-albe          #+#    #+#             */
/*   Updated: 2023/03/01 12:17:33 by fde-albe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

/*t_hit_obj	no_hit_default_values(void)
{
	t_hit_obj	hit;

	hit.t_min = 4535320;
	hit.closest_sphere = -1;
	hit.closest_plane = -1;
	hit.closest_cylinder = -1;
	hit.closest_triangle = -1;
	hit.color = 0;
	hit.normal = (t_vector){0, 0, 0};
	hit.hit_point = (t_vector){0, 0, 0};
	hit.light_absorb_ratio = 1;
	hit.refraction_index = 1;
	hit.light_absorb_distance = 1;
	hit.ks = 0.4f;
	hit.kd = 0.3f;
	return (hit);
}*/

/*void	check_hit_spheres(t_data *data, t_ray ray, t_hit_obj *hit)
{
	int			i;
	float		t;

	i = -1;
	while (++i < data->nb_objs->nb_spheres)
	{
		t = intersect_ray_sphere(ray, data->scene->spheres[i]);
		if (t)
		{
			if (t < hit->t_min)
			{
				hit->t_min = t;
				hit->closest_sphere = i;
			}
		}
	}
}*/

/*void	check_hit_planes(t_data *data, t_ray ray, t_hit_obj *hit)
{
	int			i;
	float		t;

	i = -1;
	while (++i < data->nb_objs->nb_planes)
	{
		t = intersect_ray_plane(ray, data->scene->planes[i]);
		if (t)
		{
			if (t < hit->t_min)
			{
				hit->t_min = t;
				hit->closest_plane = i;
				hit->closest_sphere = -1;
			}
		}
	}
}*/

/*void	check_cylinder_h(t_cylinder cyl, t_ray ray, t_hit_obj *hit, t_cy_h c_h)
{
	c_h.t = define_cylinder_height(cyl, ray, c_h.t);
	if (c_h.t && c_h.t < hit->t_min)
	{
		hit->t_min = c_h.t;
		hit->cylinder_face = 0;
		hit->closest_cylinder = c_h.i;
		hit->closest_sphere = -1;
		hit->closest_plane = -1;
	}
}

void	check_cylinder_t(t_cylinder cyl, t_ray ray, t_hit_obj *hit, t_cy_h c_h)
{
	c_h.t = intersect_ray_cylinder_top(ray, cyl);
	if (c_h.t && c_h.t < hit->t_min)
	{
		hit->t_min = c_h.t;
		hit->cylinder_face = 2;
		hit->closest_cylinder = c_h.i;
		hit->closest_sphere = -1;
		hit->closest_plane = -1;
	}
}

void	check_cylinder_b(t_cylinder cyl, t_ray ray, t_hit_obj *hit, t_cy_h c_h)
{
	c_h.t = intersect_ray_cylinder_bottom(ray, cyl);
	if (c_h.t && c_h.t < hit->t_min)
	{
		hit->t_min = c_h.t;
		hit->cylinder_face = 1;
		hit->closest_cylinder = c_h.i;
		hit->closest_sphere = -1;
		hit->closest_plane = -1;
	}
}

void	check_hit_cylinders(t_data *data, t_ray ray, t_hit_obj *hit)
{
	t_cy_h	c_h;

	c_h.i = -1;
	while (++c_h.i < data->nb_objs->nb_cylinders)
	{
		c_h.t = intersect_ray_cylinder(ray, data->scene->cylinders[c_h.i]);
		if (c_h.t)
		{
			check_cylinder_h(data->scene->cylinders[c_h.i], ray, hit, c_h);
			check_cylinder_t(data->scene->cylinders[c_h.i], ray, hit, c_h);
			check_cylinder_b(data->scene->cylinders[c_h.i], ray, hit, c_h);
		}
	}
}*/

/*void	check_hit_triangles(t_data *data, t_ray ray, t_hit_obj *hit)
{
	int			i;
	float		t;

	i = -1;
	while (++i < data->nb_objs->nb_triangles)
	{
		t = intersect_ray_triangle(ray, data->scene->triangles[i]);
		if (t)
		{
			if (t < hit->t_min)
			{
				hit->t_min = t;
				hit->closest_triangle = i;
				hit->closest_sphere = -1;
				hit->closest_plane = -1;
				hit->closest_cylinder = -1;
			}
		}
	}
}*/

void	hit_sphere(t_data *data, t_hit_obj *hit)
{
	int			sph;
	t_sphere	sp;

	sph = hit->closest_sphere;
	sp = data->scene->spheres[sph];
	hit->normal = vector_from_points(sp.center, hit->hit_point);
	normalize_vector(&hit->normal);
	if (sp.texture == 1)
	{
		if (checkerboard_sphere(hit->hit_point, sp) == 1)
			hit->color = sp.color;
		else
			hit->color = 0x000000;
	}
	else
		hit->color = sp.color;
	hit->light_absorb_ratio = sp.light_absorb_ratio;
	hit->refraction_index = sp.refraction_index;
	hit->light_absorb_distance = sp.light_absorb_distance;
	hit->ks = sp.ks;
	hit->kd = sp.kd;
	hit->roughness = sp.roughness;
	vector_rand(&hit->normal, hit->roughness);
}

void	hit_plane(t_data *data, t_hit_obj *hit)
{
	t_plane	pl;

	pl = data->scene->planes[hit->closest_plane];
	hit->normal = pl.normal;
	normalize_vector(&hit->normal);
	if (pl.texture == 1)
	{
		if (checkerboard_plane(hit->hit_point, pl) == 1)
			hit->color = pl.color;
		else
			hit->color = 0x000000;
	}
	else
		hit->color = pl.color;
	hit->light_absorb_ratio = pl.light_absorb_ratio;
	hit->refraction_index = pl.refraction_index;
	hit->light_absorb_distance = pl.light_absorb_distance;
	hit->ks = pl.ks;
	hit->kd = pl.kd;
	hit->roughness = pl.roughness;
	vector_rand(&hit->normal, hit->roughness);
}

void	hit_cylinder(t_data *data, t_hit_obj *hit)
{
	t_cylinder	cyl;

	cyl = data->scene->cylinders[hit->closest_cylinder];
	if (hit->cylinder_face == 0)
		hit->normal = normal_cylinder(cyl, hit->hit_point);
	else if (hit->cylinder_face == 2)
		hit->normal = cyl.normal;
	else if (hit->cylinder_face == 1)
		hit->normal = vector_scale(cyl.normal, -1);
	hit->color = cyl.color;
	hit->light_absorb_ratio = cyl.light_absorb_ratio;
	hit->refraction_index = cyl.refraction_index;
	hit->light_absorb_distance = cyl.light_absorb_distance;
	hit->ks = cyl.ks;
	hit->kd = cyl.kd;
	hit->roughness = cyl.roughness;
	vector_rand(&hit->normal, hit->roughness);
}

void	hit_triangle(t_data *data, t_hit_obj *hit)
{
	t_triangle	tr;

	tr = data->scene->triangles[hit->closest_triangle];
	hit->normal = normal_triangle(tr);
	normalize_vector(&hit->normal);
	hit->color = tr.color;
	hit->light_absorb_ratio = tr.light_absorb_ratio;
	hit->refraction_index = tr.refraction_index;
	hit->light_absorb_distance = tr.light_absorb_distance;
	hit->ks = tr.ks;
	hit->kd = tr.kd;
	hit->roughness = tr.roughness;
	vector_rand(&hit->normal, hit->roughness);
}

t_hit_obj	get_closest_intersection(t_data *data, t_ray ray)
{
	t_hit_obj	hit;

	hit = no_hit_default_values();
	check_hit_spheres(data, ray, &hit);
	check_hit_planes(data, ray, &hit);
	check_hit_cylinders(data, ray, &hit);
	check_hit_triangles(data, ray, &hit);
	if (hit.t_min < 4535320)
	{
		hit.hit_point = vector_add(ray.origin,
				vector_scale(ray.direction, hit.t_min));
		if (hit.closest_sphere != -1)
			hit_sphere(data, &hit);
		else if (hit.closest_plane != -1)
			hit_plane(data, &hit);
		else if (hit.closest_cylinder != -1)
			hit_cylinder(data, &hit);
		else if (hit.closest_triangle != -1)
			hit_triangle(data, &hit);
	}
	return (hit);
}

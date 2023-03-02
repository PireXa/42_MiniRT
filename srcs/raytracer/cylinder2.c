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

void	check_cylinder_h(t_cylinder cyl, t_ray ray, t_hit_obj *hit, t_cy_h c_h)
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
}

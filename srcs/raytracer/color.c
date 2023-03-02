/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-albe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 10:05:30 by fde-albe          #+#    #+#             */
/*   Updated: 2023/03/01 12:17:33 by fde-albe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

int	calc_color_intensity(int color, float intensity)
{
	int	r;
	int	g;
	int	b;

	r = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	b = color & 0xFF;
	r *= intensity;
	g *= intensity;
	b *= intensity;
	return ((r << 16) | (g << 8) | b);
}

int	blend_colors(int c1, int c2, float rt)
{
	int	r;
	int	g;
	int	b;

	if (rt >= 1)
		rt = 1;
	if (rt <= 0)
		rt = 0;
	r = (int)((float)((c1 >> 16) & 0xFF) *rt
			+ (float)((c2 >> 16) & 0xFF) *(1 - rt));
	g = (int)((float)((c1 >> 8) & 0xFF) *rt
			+ (float)((c2 >> 8) & 0xFF) *(1 - rt));
	b = (int)((float)((c1) & 0xFF) *rt + (float)((c2) & 0xFF) *(1 - rt));
	return (r << 16 | g << 8 | b);
}

t_hit_obj	get_reflect_color(t_data *d, t_ray rflct_ray, t_hit_obj h, float *f)
{
	t_hit_obj	reflect_hit;

	reflect_hit = get_closest_intersection(d, rflct_ray);
	if (reflect_hit.t_min < 4535320)
		reflect_hit.color = shading(reflect_hit, rflct_ray, d);
	else
	{
		*f = -5.0f;
		reflect_hit.color = h.color;
	}
	return (reflect_hit);
}

t_hit_obj	get_refract_color(t_data *d, t_ray rfrct_ray, t_hit_obj h, float *b)
{
	t_hit_obj	refract_hit;

	refract_hit = get_closest_intersection(d, rfrct_ray);
	if (refract_hit.t_min < 0.001f)
	{
		rfrct_ray.origin = vector_add(h.hit_point,
				vector_scale(rfrct_ray.direction, refract_hit.t_min + 0.01f));
		refract_hit = get_closest_intersection(d, rfrct_ray);
	}
	*b = 1.0f - expf(-h.light_absorb_distance * refract_hit.t_min);
	rfrct_ray.origin = vector_add(h.hit_point,
			vector_scale(rfrct_ray.direction, refract_hit.t_min));
	rfrct_ray.origin = vector_add(rfrct_ray.origin,
			vector_scale(refract_hit.normal, 0.001f));
	rfrct_ray.direction = calc_refracted_ray(h.refraction_index, 1.0f,
			rfrct_ray.direction, vector_scale(h.normal, -1));
	refract_hit = get_closest_intersection(d, rfrct_ray);
	if (refract_hit.t_min < 4535320)
		refract_hit.color = shading(refract_hit, rfrct_ray, d);
	else
		refract_hit.color = h.color;
	return (refract_hit);
}

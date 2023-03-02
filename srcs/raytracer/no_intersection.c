/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_intersection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-albe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 10:05:30 by fde-albe          #+#    #+#             */
/*   Updated: 2023/03/01 12:17:33 by fde-albe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

t_hit_obj	no_hit_default_values(void)
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
}

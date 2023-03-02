/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_checkerboard.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-albe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 10:05:30 by fde-albe          #+#    #+#             */
/*   Updated: 2023/03/01 12:17:33 by fde-albe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

typedef struct s_chck_pl
{
	int			flag;
	float		period;
	float		s;
	float		t;
	t_vector	u;
	t_vector	v;
}				t_chck_pl;

t_chck_pl	fix_u(t_vector hit_point, t_vector normal)
{
	t_chck_pl	chck_pl;

	chck_pl.flag = 0;
	chck_pl.period = 1.0f;
	if (normal.y == 1 || normal.y == -1)
	{
		chck_pl.u = cross_product(normal, (t_vector){1, 0, 0});
		chck_pl.flag = 1;
	}
	else
		chck_pl.u = cross_product(normal, (t_vector){0, 1, 0});
	normalize_vector(&chck_pl.u);
	chck_pl.v = cross_product(normal, chck_pl.u);
	normalize_vector(&chck_pl.v);
	chck_pl.s = dot_product(chck_pl.u, hit_point);
	chck_pl.t = dot_product(chck_pl.v, hit_point);
	return (chck_pl);
}

int	checkerboard_plane_1(t_chck_pl chck_pl, int x, int y)
{
	if (chck_pl.t < 0)
	{
		if ((x + y) % 2 == 0)
			return (chck_pl.flag - 1);
		else
			return (chck_pl.flag);
	}
	else
	{
		if ((x + y) % 2 == 0)
			return (chck_pl.flag);
		else
			return (chck_pl.flag - 1);
	}
}

int	checkerboard_plane_2(t_chck_pl chck_pl, int x, int y)
{
	if (chck_pl.t < 0)
	{
		if ((x + y) % 2 == 0)
			return (chck_pl.flag);
		else
			return (chck_pl.flag - 1);
	}
	else
	{
		if ((x + y) % 2 == 0)
			return (chck_pl.flag - 1);
		else
			return (chck_pl.flag);
	}
}

int	checkerboard_plane(t_vector hit_point, t_plane plane)
{
	int			x;
	int			y;
	t_chck_pl	chck_pl;

	chck_pl = fix_u(hit_point, plane.normal);
	x = (int)(chck_pl.s / chck_pl.period);
	y = (int)(chck_pl.t / chck_pl.period);
	if (chck_pl.s < 0)
		return (checkerboard_plane_1(chck_pl, x, y));
	else
		return (checkerboard_plane_2(chck_pl, x, y));
}

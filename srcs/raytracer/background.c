/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-albe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 10:05:30 by fde-albe          #+#    #+#             */
/*   Updated: 2023/03/01 12:17:33 by fde-albe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

typedef struct s_bckgrnd
{
	uint8_t	a;
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
}				t_bckgrnd;

typedef struct s_step
{
	float	a;
	float	r;
	float	g;
	float	b;
}				t_step;

int	background_color(int y, int color1, int color2)
{
	t_bckgrnd	start;
	t_bckgrnd	end;
	t_step		step;
	uint32_t	color;

	start.a = color1 >> 24;
	start.r = color1 >> 16;
	start.g = color1 >> 8;
	start.b = color1 >> 0;
	end.a = color2 >> 24;
	end.r = color2 >> 16;
	end.g = color2 >> 8;
	end.b = color2 >> 0;
	step.a = (end.a - start.a) / WIND_H;
	step.r = (end.r - start.r) / WIND_H;
	step.g = (end.g - start.g) / WIND_H;
	step.b = (end.b - start.b) / WIND_H;
	color = 0 | ((int)(start.a + y * step.a) & 0xFF) << 24
		| ((int)(start.r + y * step.r) & 0xFF) << 16
		| ((int)(start.g + y * step.g) & 0xFF) << 8
		| ((int)(start.b + y * step.b) & 0xFF) << 0;
	return (color);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fresnel.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-albe <rdas-nev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 4242/42/42 42:42:42 by rdas-nev          #+#    #+#             */
/*   Updated: 4242/42/42 42:42:42 by rdas-nev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

typedef struct s_fresnel
{
	float		n;
	float		n1;
	float		r0;
	float		cos_theta;
	float		sin_theta;
	float		x;
}				t_fresnel;

float	fresnel(float n2, t_vector i_dir, t_vector nor, float l_rflct)
{
	float		ret;
	t_fresnel	f;

	f.n1 = 1.00f;
	f.r0 = powf((f.n1 - n2) / (f.n1 + n2), 2);
	f.cos_theta = -dot_product(nor, i_dir);
	if (f.n1 > n2)
	{
		f.n = f.n1 / n2;
		f.sin_theta = f.n * f.n * (1 - f.cos_theta * f.cos_theta);
		if (f.sin_theta > 1)
			return (1.0f);
		f.cos_theta = sqrtf(1 - f.sin_theta);
	}
	f.x = 1.0f - f.cos_theta;
	ret = f.r0 + (1.0f - f.r0) * powf(f.x, 5);
	ret = l_rflct + (1.0f - l_rflct) * ret;
	return (ret);
}

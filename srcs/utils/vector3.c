/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-albe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 10:05:30 by fde-albe          #+#    #+#             */
/*   Updated: 2023/03/01 12:17:33 by fde-albe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

t_vector	transform_vector(t_vector v, float **matrix)
{
	t_vector	result;

	result.x = v.x * matrix[0][0] + v.y * matrix[1][0] + v.z * matrix[2][0];
	result.y = v.x * matrix[0][1] + v.y * matrix[1][1] + v.z * matrix[2][1];
	result.z = v.x * matrix[0][2] + v.y * matrix[1][2] + v.z * matrix[2][2];
	return (result);
}

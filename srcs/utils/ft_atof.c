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

float	ft_atof(char *str)
{
	float	result;
	float	decimal;
	float	sign;
	int		i;

	result = 0;
	decimal = 0;
	sign = 1;
	i = 0;
	if (ft_strncmp(str, "0", 2) == 0)
		return (0.00001f);
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (str[i] && str[i] != '.' && str[i] != '\n')
		result = result * 10 + (float)str[i++] - '0';
	if (str[i] == '.')
		i++;
	while (str[i] && str[i] != '\n')
		decimal = decimal * 10 + (float)str[i++] - '0';
	while (i && str[--i] != '.')
		decimal /= 10;
	return ((result + decimal) * sign);
}

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
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (str[i] && str[i] != '.')
	{
		result = result * 10 + str[i] - '0';
		i++;
	}
	if (str[i] == '.')
		i++;
	while (str[i])
	{
		decimal = decimal * 10 + str[i] - '0';
		i++;
	}
	while (str[--i] != '.')
		decimal /= 10;
	return ((result + decimal) * sign);
}

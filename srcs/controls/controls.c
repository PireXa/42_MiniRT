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

int	key_press(int key, t_data *data)
{
	char		*cmd;
	char		**obj_code;
	static char	code[3];
	static int	n;

	key = key_converter1(key);
	key = key_converter2(key);
	if (key == key_TAB)
	{
		cmd = print_message(cmd);
		obj_code = ft_split(cmd, ' ');
		code[0] = ft_itoa(checkcode(obj_code[0], data))[0];
		n = ft_atoi(obj_code[1]);
		free_editor(obj_code, cmd, data);
	}
	key_out(key, data);
	key_translations(data, key, code, n);
	key_resize(data, key, code, n);
	key_rotation(data, key, code, n);
	key_height(data, key, code, n);
	return (0);
}

void	controls(t_data *data)
{
	mlx_hook(data->mlx_win, 2, 1L << 0, key_press, data);
	mlx_hook(data->mlx_win, 17, 1L << 17, free_all, data);
}

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

void	fps(t_data *data)
{
	char	*fps;
	char	*fps_str;

	if (data->fps.frame_time < time(NULL))
	{
		data->fps.fps = data->fps.frame_ctr;
		data->fps.frame_ctr = 0;
		data->fps.frame_time = time(NULL);
	}
	fps = ft_itoa(data->fps.fps);
	fps_str = ft_strjoin("FPS: ", fps);
	mlx_string_put(data->mlx, data->mlx_win, 10, 100, 0x000000, fps_str);
	free(fps);
	free(fps_str);
	data->fps.frame_ctr++;
}

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*ptr;

	ptr = b;
	while (len-- > 0)
		*ptr++ = c;
	return (b);
}

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

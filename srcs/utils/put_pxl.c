#include "../../inc/minirt.h"

void    put_pxl(t_img *img, int x, int y, int color)
{
	char    *dst;

	if (x >= 0 && x < WIND_W && y >= 0 && y < WIND_H)
	{
		dst = img->addr + (y * img->line_length + x * (img->bi_per_pxl / 8));
		*(unsigned int*)dst = color;
	}
}

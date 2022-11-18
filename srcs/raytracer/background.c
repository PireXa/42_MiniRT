#include "../../inc/minirt.h"

int background_color(int y, int color1, int color2)
{
	int color;
	int gradient;

	gradient = fabs(color2 - color1) / 255;
	color = color1 + (gradient * y / (int)WIND_H);
	return (color);
}
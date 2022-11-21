#include "../../inc/minirt.h"

int background_color(int y, int color1, int color2)
{
	uint8_t start_a = color1 >> 24;
	uint8_t start_r = color1 >> 16;
	uint8_t start_g = color1 >> 8;
	uint8_t start_b = color1 >> 0;
	uint8_t end_a = color2 >> 24;
	uint8_t end_r = color2 >> 16;
	uint8_t end_g = color2 >> 8;
	uint8_t end_b = color2 >> 0;

	float step_a = (float)(end_a - start_a) / WIND_H;
	float step_r = (float)(end_r - start_r) / WIND_H;
	float step_g = (float)(end_g - start_g) / WIND_H;
	float step_b = (float)(end_b - start_b) / WIND_H;
	uint32_t color = 0 | ((int)(start_a + y * step_a) & 0xFF) << 24 | ((int)(start_r + y * step_r) & 0xFF) << 16 |
					 ((int)(start_g + y * step_g) & 0xFF) << 8 | ((int)(start_b + y * step_b) & 0xFF) << 0;
	return (color);
}

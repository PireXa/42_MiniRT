#include "../../inc/minirt.h"

void	render_progress_bar(int x)
{
	int i;
	int left_i;

	printf("Progress: %d%% | ", (int) ((float) x / WIND_W * 100));
	i = (int) ((float) x / WIND_W * 50);
	left_i = 50 - i - 1;
	while (i--)
		printf("#");
	while (left_i--)
		printf("-");
	printf("\r");
}
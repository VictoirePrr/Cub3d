#include "cub3d.h"


int main(void)
{
	void *mlx = mlx_init();
	void *win = mlx_new_window(mlx, 1000, 500, "Empty window");
	(void)win;
	mlx_loop(mlx);
	return (0);
}


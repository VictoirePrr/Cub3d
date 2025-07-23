#include "cub3d.h"
#include "pars.h"

int	validate_args(int argc)
{
	if (argc != 2)
	{
		ft_printf("Error: Usage: ./cub3D map.cub\n");
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_cub3d	cub3d;

	if (argc != 2)
	{
		ft_printf("Error: Usage: ./cub3D map.cub\n");
		return (1);
	}
	if (init_cub3d(&cub3d, argv[1]) != 0)
		return (1);
	render_frame(&cub3d);
	mlx_hook(cub3d.mlx->win_ptr, 2, 1L << 0, handle_keypress, &cub3d);
	mlx_hook(cub3d.mlx->win_ptr, 3, 1L << 1, handle_keyrelease, &cub3d);
	mlx_hook(cub3d.mlx->win_ptr, 17, 0, handle_close, &cub3d);
	mlx_hook(cub3d.mlx->win_ptr, 6, 1L << 6, handle_mouse, &cub3d);
	mlx_loop_hook(cub3d.mlx->mlx_ptr, game_loop, &cub3d);
	mlx_loop(cub3d.mlx->mlx_ptr);
	return (0);
}

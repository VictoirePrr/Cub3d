#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "mlx.h"
# include "pars.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <math.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define WIN_WIDTH 1024
# define WIN_HEIGHT 768
# define WIN_TITLE "Cub3D"

# define ESC 65307
# define UP 65362
# define RIGHT 65363
# define LEFT 65361
# define DOWN 65364

# define W 119
# define A 97
# define S 115
# define D 100

typedef struct s_mlx
{
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_ptr;
	char			*img_data;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}					t_mlx;

typedef struct s_cub3d
{
	struct s_game	*game;
	t_mlx			*mlx;
}					t_cub3d;

// ============== mlx_init.c ==============
int					init_mlx(t_cub3d *cub3d);
int					create_window(t_cub3d *cub3d);
int					create_image(t_cub3d *cub3d);
void				cleanup_mlx(t_cub3d *cub3d);
int					handle_close(t_cub3d *cub3d);

// ============== event.c ==============
int					handle_keypress(int keycode, t_cub3d *cub3d);

#endif
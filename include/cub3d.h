
#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "mlx.h"
// # include <X11/X.h>
// # include <X11/keysym.h>
# include <fcntl.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define WALL_XPM "sprites/blue.xpm"
# define FLOOR_XPM "sprites/red.xpm"

# define XPM_HEIGHT 64
# define XPM_WIDTH 64

# define ESC 65307
# define UP 65362
# define RIGHT 65363
# define LEFT 65361
# define DOWN 65364

# define WALL '1'
# define FLOOR '0'

# define W 119
# define A 97
# define S 115
# define D 100

typedef struct s_keys
{
	int			up;
	int			down;
	int			left;
	int			right;
}				t_keys;

typedef struct s_img
{
	void		*image;
	int			width;
	int			height;

}				t_img;

typedef struct s_matrix
{
	char		**map;
	size_t		htl;
	size_t		vtl;
}				t_matrix;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	float			start_x;
	float			start_y;
	t_matrix	matrix;
	t_img		floor;
	t_img		wall;
	t_keys		keys;
}				t_data;

#endif
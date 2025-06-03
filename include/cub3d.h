
#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "mlx.h"
# include <X11/X.h>      // COMMENTER SUR MAC
# include <X11/keysym.h> // COMMENTER SUR MAC
# include <fcntl.h>
# include <math.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define WALL_XPM "sprites/blue.xpm"
# define FLOOR_XPM "sprites/red.xpm"
# define PLAYER_XPM "sprites/player.xpm"

# define MOVE_SPEED 0.1
# define ROTATE_SPEED 0.05

# define XPM_HEIGHT 64
# define XPM_WIDTH 64

# define ESC 65307
# define UP 65362
# define RIGHT 65363
# define LEFT 65361
# define DOWN 65364

# define WALL '1'
# define FLOOR '0'
# define PLAYER "NSEW"

# define W 119
# define A 97
# define S 115
# define D 100

typedef struct s_player
{
	float		x;
	float		y;
	float		dir_x;
	float		dir_y;

	int			move_forward;
	int			move_backward;
	int			move_left;
	int			move_right;
	int			rotate_left;
	int			rotate_right;
}				t_player;

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
	float		start_x;
	float		start_y;
	t_matrix	matrix;
	t_img		floor;
	t_img		wall;
	t_img		img_player;
	t_keys		keys;
	t_player	player;
}				t_data;

// utils
void			free_all(char **matrix);
char			*dup_temp(const char *s1);
void			put_img_to_window(t_data *data, t_img img, int vtl, int htl);
int				closing_game(t_data *data);
int				key_press(int key, void *param);
int				key_release(int key, void *param);

// player_moves
void			move_forward(t_data *data);
void			move_backward(t_data *data);
void			move_left(t_data *data);
void			move_right(t_data *data);
void			rotate_left(t_data *data);
void			rotate_right(t_data *data);

// temp_pars
char			**fill_the_matrix(const char *file, t_matrix *matrix);
char			**read_map(const char *file, t_matrix *matrix);
t_img			put_xpm_to_img(void *xvar, char *xpm, t_img *img);
void			init_img(t_data *data, t_img *img);
void			set_up_game(t_data *data);
void			render_img(t_data *data, int vtl, int htl);

// handle_player
int				update_player_pos(t_data *data);
void			set_dir(char *c, t_data *data);
void			draw_player(t_data *data);

#endif
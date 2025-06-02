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

// ============== FORWARD DECLARATIONS ==============
// Déclarer les structures avant de les utiliser
struct s_game;

# define WIN_WIDTH 1024
# define WIN_HEIGHT 768
# define WIN_TITLE "Cub3D"

# define MOVE_SPEED 10
# define ROTATE_SPEED 0.5
# define ESC 65307
# define UP 65362 // BIF BOF
# define RIGHT 65363
# define LEFT 65361
# define DOWN 65364 // bif bof
# define PI 3.14159265358979323846
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

typedef struct s_camera
{
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
}					t_camera;

typedef struct s_cub3d
{
	struct s_game	*game;
	t_mlx			*mlx;
	t_camera		*camera;  // Pas besoin de struct ici car c'est défini au-dessus
}					t_cub3d;

// ============== mlx_init.c ==============
int					init_mlx(t_cub3d *cub3d);
int					create_window(t_cub3d *cub3d);
int					create_image(t_cub3d *cub3d);
void				cleanup_mlx(t_cub3d *cub3d);
int					handle_close(t_cub3d *cub3d);

// ============== event.c ==============
int					handle_keypress(int keycode, t_cub3d *cub3d);
void				handle_camera_movement(int keycode, t_cub3d *cub3d);

// ============== render.c ==============
void				render_frame(t_cub3d *cub3d);
void				put_pixel(t_cub3d *cub3d, int x, int y, int color);

//============== camera_init.c ==============
int					init_camera(t_cub3d *cub3d);
void				set_direction_from_orientation(t_camera *camera,
						char orientation);
void				update_camera_plane(t_camera *camera);
void				cleanup_camera(t_cub3d *cub3d);

// ============== cam_mouv.c ==============
// Utiliser struct s_game au lieu de t_game dans les déclarations
int					check_wall(struct s_game *game, double x, double y);
void				move_camera(t_cub3d *cub3d, double move_x, double move_y);
void				rotate_camera(t_camera *camera, double rotation);

#endif
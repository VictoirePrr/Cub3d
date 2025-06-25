#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "mlx.h"
# include "pars.h"
# include <X11/X.h> // commenter sur mac
# include <X11/keysym.h> // commenter sur mac
# include <fcntl.h>
# include <math.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

struct s_game;
struct s_textures;

# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080
# define WIN_TITLE "Cub3D"

# define MOVE_SPEED 0.04
# define ROTATE_SPEED 0.02
# define ROTATE_SPEED_MOUSE 0.04
# define STEP_SIZE 0.05
# define MAX_STEPS 1000
# define ESC 65307
# define UP 65362 // BIF BOF
# define RIGHT 65361
# define LEFT 65363
# define DOWN 65364 // bif bof
# define PI 3.14159265358979323846
# define W 119
# define A 97
# define S 115
# define D 100
# define TEXTURE_WIDTH 64
# define TEXTURE_HEIGHT 64

typedef struct s_keys
{
	int				w;
	int				a;
	int				s;
	int				d;
	int				left;
	int				right;
	int				esc;
}					t_keys;

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

typedef struct s_ray
{
	double			ray_dir_x;
	double			ray_dir_y;
	int				map_x;
	int				map_y;
	double			side_dist_x;
	double			side_dist_y;
	double			delta_dist_x;
	double			delta_dist_y;
	double			perp_wall_dist;
	int				step_x;
	int				step_y;
	int				hit;
	int				side;
}					t_ray;

typedef struct s_wall_params
{
	int				line_height;
	int				draw_start;
	int				draw_end;
	double			wall_x;
	int				tex_x;
	double			step;
	double			tex_pos;
}					t_wall_params;

typedef struct s_cub3d
{
	struct s_game	*game;
	t_mlx			*mlx;
	t_camera		*camera;
	t_keys			*keys;
	int				last_mouse_x;

}					t_cub3d;

// ============== mlx_init.c ==============
int					init_mlx(t_cub3d *cub3d);
int					create_window(t_cub3d *cub3d);
int					create_image(t_cub3d *cub3d);
void				cleanup_mlx(t_cub3d *cub3d);
int					handle_close(t_cub3d *cub3d);
int					init_textures(t_cub3d *cub3d);

// ============== event.c ==============
void				print_camera_debug(t_camera *camera);

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
int					check_wall(struct s_game *game, double x, double y);
void				move_camera(t_cub3d *cub3d, double move_x, double move_y);
void				rotate_camera(t_camera *camera, double rotation);

//============== keys.c ===================
int					handle_keypress(int keycode, t_cub3d *cub3d);
int					handle_keyrelease(int keycode, t_cub3d *cub3d);
int					game_loop(t_cub3d *cub3d);
int					init_keys(t_cub3d *cub3d);
void				cleanup_keys(t_cub3d *cub3d);
int					handle_mouse(int x, int y, t_cub3d *cub3d);

// ============== texture_utils.c ==============
void				calc_bounds(t_ray *ray, t_wall_params *p);
t_textures			*get_texture(t_cub3d *cub3d, t_ray *ray);
double				get_wall_x(t_cub3d *cub3d, t_ray *ray);
int					get_tex_x(double wall_x, t_ray *ray);
void				draw_column(t_cub3d *cub3d, int x, t_wall_params *p,
						t_textures *texture);

// ============== colors_utils.c ==============
int					get_texture_color(t_textures *texture, int tex_x,
						int tex_y);
void				put_pixel(t_cub3d *cub3d, int x, int y, int color);
int					create_rgb(int r, int g, int b);
void				render_ceiling(t_cub3d *cub3d);
void				render_floor(t_cub3d *cub3d);

// ============== calc_utils.c ==============
void				set_ray_side_dist(t_cub3d *cub3d, t_ray *ray, double next_x,
						double next_y);
void				set_ray_step(t_ray *ray, double *next_x,
						double *next_y);
void				init_data(t_cub3d *cub3d, t_ray *ray, int column);
void				calculate_wall_distance(t_cub3d *cub3d, t_ray *ray);

#endif

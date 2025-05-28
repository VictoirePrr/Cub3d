#ifndef PARS_H
# define PARS_H

# include "cub3d.h"

typedef struct s_map
{
	char		**grid;
	int			width;
	int			height;

}				t_map;

typedef struct s_textures
{
	char		*north;
	char		*south;
	char		*west;
	char		*east;
}				t_textures;

typedef struct s_colors
{
	int			r;
	int			g;
	int			b;
}				t_colors;

typedef struct s_player
{
	int			x;
	int			y;
	char		orientation;
}				t_player;

typedef struct s_game
{
	t_textures	*textures;
	t_colors	*floor;
	t_colors	*roof;
	t_map		*map;
	t_player	*player;
}				t_game;

//////////////////PARSING//////////////////////////////////////

//////////////////tools.c//////////////////////////////////////////
int				map_line(char *line);
int				is_player_char(char c);
void			parse_color(char *color_str, t_colors *color);
void			exit_error(char *str);
void			parse_map(char *line);

///////////////check_map.c///////////////////////////////////////////
int				empty_line(char *line);
int				check_config(char *line);
void			parse_config(char *line, t_game *game);
int				validate_config(t_game *game);
int				parse_file(char *filename, t_game *game);

#endif
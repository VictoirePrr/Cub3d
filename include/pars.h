#ifndef PARS_H
#define PARS_H

#include "cub3d.h"

typedef struct s_map
{
	char **grid;
	int width;
	int height;

}		t_map;

typedef struct s_textures
{
	char	*north;
	char	*south;
	char	*west;
	char	*east;
}	t_textures;

typedef struct s_colors
{
	int r;
	int g; 
	int b;
}	t_colors;

typedef struct s_player
{
	int		x;
	int		y;
	char	orientation;
}	t_player;

typedef struct s_game
{
	t_textures	*textures;
	t_colors	*floor;
	t_colors	*roof; 
	t_map		*map;
	t_player	*player;
}	t_game;


#endif
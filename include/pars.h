#ifndef PARS_H
# define PARS_H

# include "cub3d.h"

typedef struct s_map
{
	char				**grid;
	int					width;
	int					height;
}						t_map;

typedef struct s_textures
{
	char				*north;
	char				*south;
	char				*west;
	char				*east;
}						t_textures;

typedef struct s_colors
{
	int					r;
	int					g;
	int					b;
}						t_colors;

typedef struct s_player
{
	int					x;
	int					y;
	char				orientation;
}						t_player;

typedef struct s_game
{
	t_textures			*textures;
	t_colors			*floor;
	t_colors			*roof;
	t_map				*map;
	t_player			*player;
}						t_game;

typedef struct s_map_line
{
	char				*line;
	struct s_map_line	*next;
}						t_map_line;


// ============== ERROR.C ==============
int						print_error(char *str);
int						exit_error_cleanup(t_game *game, char *str, int fd);
int						exit_error(t_game *game, char *str);
int						error_return(char *str);
int						error_return_line(char *str, char *line, int fd);

// ============== CLEANUP.C ==============
void					free_split(char **split);
void					cleanup_textures(t_textures *textures);
void					cleanup_map(t_map *map);
void					cleanup_game(t_game *game);

// ============== INIT.C ==============
t_game					*init_game(void);

// ============== PARSE_COLOR.C ==============
int						parse_color_secure(char *color_str, t_colors *color,
							t_game *game);

// ============== PARSE_CONFIG.C ==============
int						parse_config_secure(char *line, t_game *game);
int						validate_config_secure(t_game *game);

// ============== PARSE_FILE.C ==============
int						parse_file_secure(char *filename, t_game *game);

// ============== PARSE_MAP.C ==============
int						parse_map_from_fd(int fd, t_game *game,char *old_line);
int						finalize_map_parsing(t_game *game,
							t_map_line *map_lines);

// ============== TOOLS.C ==============
int						map_line(char *line);
int						is_player_char(char c);
int 					is_wall_or_space(char c);
int						validate_borders(t_game *game);


// ============== UTILS.C ==============
int						get_max_width(t_map_line *head);
int						count_map_lines(t_map_line *head);
t_map_line				*create_map_line(char *line);
int						validate_char(char c);
int						check_position(t_game *game, int i, int j);

// ============== FREE.C ==============
void					free_map_lines(t_map_line *head);
int						allocate_grid(t_game *game);

// ============== CHECK_MAP.C ==============
int						empty_line(char *line);
int						check_config(char *line);

#endif
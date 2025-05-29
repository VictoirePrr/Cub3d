#include "pars.h"

int	map_line(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (0);
	while (line[i])
	{
		if (line[i] == '1' || line[i] == '0' || is_player_char(line[i]))
			return (1);
		i++;
	}
	return (0);
}

int	is_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	is_wall_or_space(char c)
{
	return (c == '1' || is_player_char(c) || c == '0');
}

int	validate_borders(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map->height)
	{
		j = 0;
		while (j < game->map->width)
		{
			if (game->map->grid[i][j] == '0'
				|| is_player_char(game->map->grid[i][j]))
			{
				if (check_position(game, i, j) != 0)
					return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

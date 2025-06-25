#include "pars.h"

void	fill_grid_line(char *dest, char *src, int width)
{
	int	i;
	int	src_len;

	src_len = ft_strlen(src);
	i = 0;
	while (i < src_len && i < width)
	{
		dest[i] = src[i];
		i++;
	}
	while (i < width)
	{
		dest[i] = ' ';
		i++;
	}
	dest[width] = '\0';
}

int	convert_to_grid(t_game *game, t_map_line *head)
{
	int			i;
	t_map_line	*current;

	i = 0;
	current = head;
	while (current && i < game->map->height)
	{
		fill_grid_line(game->map->grid[i], current->line, game->map->width);
		current = current->next;
		i++;
	}
	return (0);
}

int	find_player(t_game *game)
{
	int	i;
	int	j;
	int	player_count;

	player_count = 0;
	i = -1;
	while (++i < game->map->height)
	{
		j = -1;
		while (++j < game->map->width)
		{
			if (is_player_char(game->map->grid[i][j]))
			{
				game->player->x = j;
				game->player->y = i;
				game->player->orientation = game->map->grid[i][j];
				player_count++;
			}
			else if (!validate_char(game->map->grid[i][j]))
				return (error_return("Invalid character in map"));
		}
	}
	if (player_count != 1)
		return (error_return("Map must have exactly one player"));
	return (0);
}

t_map_line	*init_first_map_line(char *old_line)
{
	t_map_line	*map_lines;

	map_lines = create_map_line(old_line);
	free(old_line);
	if (!map_lines)
		return (NULL);
	return (map_lines);
}

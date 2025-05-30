#include "pars.h"

static void	print_map_debug(t_game *game)
{
	char	c;

	int i, j;
	ft_printf("\n  PARSED MAP (size: %dx%d):\n", game->map->width,
		game->map->height);
	ft_printf("\n");
	for (i = 0; i < game->map->height; i++)
	{
		for (j = 0; j < game->map->width; j++)
		{
			c = game->map->grid[i][j];
			if (c == ' ')
				ft_printf("·");
			else
				ft_printf("%c", c);
		}
		ft_printf("\n");
	}
	ft_printf("\n");
}

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

int	parse_map_from_fd(int fd, t_game *game, char *old_line)
{
	char		*line;
	t_map_line	*map_lines;
	t_map_line	*current;
	t_map_line	*new_line;

	map_lines = create_map_line(old_line);
	free(old_line);
	if (!map_lines)
		return (error_return("Memory allocation failed"));
	line = get_next_line(fd);
	while (line != NULL)
	{
		// if (!empty_line(line))
		// {
			new_line = create_map_line(line);
			if (!new_line)
			{
				free(line);
				free_map_lines(map_lines);
				return (error_return("Memory allocation failed"));
			}
			if (!map_lines)
				map_lines = new_line;
			else
			{
				current = map_lines;
				while (current->next)
					current = current->next;
				current->next = new_line;
			}
	//	}
		free(line);
		line = get_next_line(fd);
	}
	return (finalize_map_parsing(game, map_lines));
}

int	finalize_map_parsing(t_game *game, t_map_line *map_lines)
{
	// if (!map_lines)
	// 	return (error_return("Empty map"));
	game->map->height = count_map_lines(map_lines);
	game->map->width = get_max_width(map_lines);
	if (game->map->height < 3 || game->map->width < 3)
	{
		free_map_lines(map_lines);
		return (error_return("Map too small"));
	}
	if (allocate_grid(game) != 0)
	{
		free_map_lines(map_lines);
		return (1);
	}
	if (convert_to_grid(game, map_lines) != 0)
	{
		free_map_lines(map_lines);
		return (1);
	}
	print_map_debug(game);
	if (find_player(game) != 0 || validate_borders(game) != 0)
	{
		free_map_lines(map_lines);
		return (1);
	}
	free_map_lines(map_lines);
	return (0);
}

#include "pars.h"

int	add_line_to_map(t_map_line **map_lines, char *line)
{
	t_map_line	*new_line;
	t_map_line	*current;

	new_line = create_map_line(line);
	if (!new_line)
		return (1);
	if (!*map_lines)
		*map_lines = new_line;
	else
	{
		current = *map_lines;
		while (current->next)
			current = current->next;
		current->next = new_line;
	}
	return (0);
}

int	read_and_process_lines(int fd, t_map_line **map_lines)
{
	char	*line;

	line = get_next_line(fd);
	while (line != NULL)
	{
		if (add_line_to_map(map_lines, line) != 0)
		{
			free(line);
			free_map_lines(*map_lines);
			return (error_return("Memory allocation failed"));
		}
		free(line);
		line = get_next_line(fd);
	}
	return (0);
}

int	parse_map_from_fd(int fd, t_game *game, char *old_line)
{
	t_map_line	*map_lines;

	map_lines = init_first_map_line(old_line);
	if (!map_lines)
		return (error_return("Memory allocation failed"));
	if (read_and_process_lines(fd, &map_lines) != 0)
		return (1);
	return (finalize_map_parsing(game, map_lines));
}

int	finalize_map_parsing(t_game *game, t_map_line *map_lines)
{
	game->map->height = count_map_lines(map_lines);
	game->map->width = get_max_width(map_lines);
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
	if (find_player(game) != 0 || validate_borders(game) != 0)
	{
		free_map_lines(map_lines);
		return (1);
	}
	free_map_lines(map_lines);
	return (0);
}

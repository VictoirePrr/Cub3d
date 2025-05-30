#include "pars.h"

int	get_max_width(t_map_line *head)
{
	int			max_width;
	int			current_width;
	t_map_line	*current;

	max_width = 0;
	current = head;
	while (current)
	{
		current_width = ft_strlen(current->line);
		if (current_width > max_width)
			max_width = current_width;
		current = current->next;
	}
	return (max_width);
}

int	count_map_lines(t_map_line *head)
{
	int			count;
	t_map_line	*current;

	count = 0;
	current = head;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

t_map_line	*create_map_line(char *line)
{
	t_map_line	*new_line;
	char		*trimmed;

	trimmed = ft_strtrim(line, "\n");
	if (!trimmed)
		return (NULL);
	new_line = malloc(sizeof(t_map_line));
	if (!new_line)
	{
		free(trimmed);
		return (NULL);
	}
	new_line->line = trimmed;
	new_line->next = NULL;
	return (new_line);
}

int	validate_char(char c)
{
	return (c == '0' || c == '1' || c == ' ' || c == 'N' || c == 'S' || c == 'E'
		|| c == 'W' || c == '\t');
}

int	check_position(t_game *game, int i, int j)
{
	if (i == 0 || i == game->map->height - 1 || j == 0 || j == game->map->width
		- 1)
		return (error_return("Map not closed by walls"));
	if (!is_wall_or_space(game->map->grid[i - 1][j])
		|| !is_wall_or_space(game->map->grid[i + 1][j])
		|| !is_wall_or_space(game->map->grid[i][j - 1])
		|| !is_wall_or_space(game->map->grid[i][j + 1]))
		return (error_return("Map not closed by walls"));
	return (0);
}

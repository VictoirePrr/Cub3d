#include "pars.h"

int	validate_filename(char *filename)
{
	if (!filename || ft_strlen(filename) < 4)
		return (0);
	if (ft_strcmp(filename + ft_strlen(filename) - 4, ".cub") != 0)
		return (0);
	return (1);
}

int	handle_config_line(char *line, t_game *game, int *config_count)
{
	if (parse_config_secure(line, game) != 0)
		return (1);
	(*config_count)++;
	if (*config_count == 6)
	{
		if (validate_config_secure(game) != 0)
			return (1);
	}
	return (0);
}

int	process_line(char *line, t_game *game, int *map_start, int *config_count)
{
	if (empty_line(line))
		return (0);
	if (!*map_start)
	{
		if (check_config(line))
			return (handle_config_line(line, game, config_count));
		else if (map_line(line))
		{
			if (*config_count != 6)
				return (error_return("Map found before all configs"));
			*map_start = 1;
			return (2);
		}
		else
			return (error_return("Invalid line format"));
	}
	return (0);
}

static int	process_file_lines(int fd, t_game *game, int *config_count)
{
	char	*line;
	int		map_start;
	int		result;

	map_start = 0;
	line = get_next_line(fd);
	while (line != NULL && !map_start)
	{
		result = process_line(line, game, &map_start, config_count);
		if (result == 1)
			return (error_return_line("Parsing error", line, fd));
		else if (result == 2)
		{
			if (parse_map_from_fd(fd, game, line) != 0)
				return (1);
			return (0);
		}
		free(line);
		line = get_next_line(fd);
	}
	return (2);
}

int	parse_file_secure(char *filename, t_game *game)
{
	int	fd;
	int	config_count;
	int	result;

	if (!validate_filename(filename))
		return (error_return("Invalid file extension"));
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (error_return("Cannot open file"));
	config_count = 0;
	result = process_file_lines(fd, game, &config_count);
	close(fd);
	if (result == 1)
		return (1);
	if (result == 0)
		return (0);
	if (config_count != 6)
		return (error_return("Missing configuration elements"));
	return (error_return("No map found"));
}

#include "pars.h"

int	empty_line(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (1);
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

int	check_config(char *line)
{
	char	*trimmed;
	int		result;

	trimmed = ft_strtrim(line, " \t");
	if (!trimmed)
		return (0);
	result = (ft_strncmp(trimmed, "NO ", 3) == 0 || ft_strncmp(trimmed, "SO ",
				3) == 0 || ft_strncmp(trimmed, "WE ", 3) == 0
			|| ft_strncmp(trimmed, "EA ", 3) == 0 || ft_strncmp(trimmed, "F ",
				2) == 0 || ft_strncmp(trimmed, "C ", 2) == 0);
	free(trimmed);
	return (result);
}

void	parse_config(char *line, t_game *game)
{
	char	**tokens;
	char	*trimmed;

	trimmed = ft_strtrim(line, " \t");
	tokens = ft_split(trimmed, ' ');
	free(trimmed);
	if (!tokens || !tokens[0] || !tokens[1])
	{
		// exit_error("Invalid configuration line");
		if (ft_strcmp(tokens[0], "NO") == 0)
		{
			if (game->textures->north)
				// exit_error("Duplicate north texture");
				game->textures->north = ft_strdup(tokens[1]);
		}
		else if (ft_strcmp(tokens[0], "SO") == 0)
		{
			if (game->textures->south)
				// exit_error("Duplicate south texture");
				game->textures->south = ft_strdup(tokens[1]);
		}
		else if (ft_strcmp(tokens[0], "WE") == 0)
		{
			if (game->textures->west)
				// exit_error("Duplicate west texture");
				game->textures->west = ft_strdup(tokens[1]);
		}
		else if (ft_strcmp(tokens[0], "EA") == 0)
		{
			if (game->textures->east)
				// exit_error("Duplicate east texture");
				game->textures->east = ft_strdup(tokens[1]);
		}
		else if (ft_strcmp(tokens[0], "F") == 0)
		{
			if (game->floor)
				// exit_error("Duplicate floor color");
				parse_color(tokens[1], game->floor);
		}
		else if (ft_strcmp(tokens[0], "C") == 0)
		{
			if (game->roof)
				// exit_error("Duplicate roof color");
				parse_color(tokens[1], game->roof);
		}
	}
	free_split(tokens);
}

int	validate_config(t_game *game)
{
	return (game->textures->north && game->textures->south
		&& game->textures->west && game->textures->east && game->floor != NULL
		&& game->roof != NULL);
}

int	parse_file(char *filename, t_game *game)
{
	char	*line;
	int		fd;
	int		map_start;
	int		config_count;

	map_start = 0;
	config_count = 0;
	if (!filename || ft_strlen(filename) < 4 || ft_strcmp(filename
			+ ft_strlen(filename) - 4, ".cub") != 0)
		exit_error("Invalid file");
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		exit_error("Cannot open file");
	ft_memset(game, 0, sizeof(t_game));
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (!empty_line(line))
		{
			if (!map_start)
			{
				if (check_config(line))
				{
					parse_config(line, game);
					config_count++;
					if (config_count == 6)
					{
						if (!validate_config)
						 exit_error("Error Config"); //leaks 
					}
				}
			}
			else if (map_line(line))
			{
				if(config_count != 6)
					exit_error("Error Config"); //leaks 
				map_start = 1;
				parse_map(line);
			}
			else
				exit_error("Error line format"); //leaks 
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (config_count != 6)
		exit_error("Missing configuration elements"); //leaks
	return (0);
}

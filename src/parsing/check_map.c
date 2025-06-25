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

int	validate_config_secure(t_game *game)
{
	if (!game->north->filename || !game->south->filename
		|| !game->west->filename || !game->east->filename)
		return (error_return("Missing texture(s)"));
	if (game->floor->r == -1 || game->roof->r == -1)
		return (error_return("Missing color(s)"));
	return (0);
}

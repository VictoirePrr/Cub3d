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

void	parse_color(char *color_str, t_colors *color)
{
	char **rgb;
	int r, g, b;

	rgb = ft_split(color_str, ',');
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
		//exit_error("Invalid color format");

	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);

	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		//exit_error("Color values must be between 0 and 255");

	color->r = r;
	color->g = g;
	color->b = b;

	free_split(rgb);
}

void	exit_error(char *str)
{
	printf("Error : %s\n", str);
	exit(1);
}

void parse_map(char *line)
{
	return ;
}
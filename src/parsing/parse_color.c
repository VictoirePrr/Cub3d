#include "pars.h"

int	validate_rgb_values(int r, int g, int b)
{
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (0);
	return (1);
}

int	parse_rgb_tokens(char **rgb, t_colors *color)
{
	color->r = ft_atoi(rgb[0]);
	color->g = ft_atoi(rgb[1]);
	color->b = ft_atoi(rgb[2]);
	return (validate_rgb_values(color->r, color->g, color->b));
}

int	validate_rgb_format(char **rgb)
{
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
		return (0);
	return (1);
}

int	parse_color_secure(char *color_str, t_colors *color, t_game *game)
{
	char	**rgb;
	int		result;

	(void)game;
	if (color->r != -1)
		return (error_return("Duplicate color definition"));
	rgb = ft_split(color_str, ',');
	if (!validate_rgb_format(rgb))
	{
		free_split(rgb);
		return (error_return("Invalid color format"));
	}
	result = parse_rgb_tokens(rgb, color);
	free_split(rgb);
	if (!result)
		return (error_return("Color values must be between 0 and 255"));
	return (0);
}

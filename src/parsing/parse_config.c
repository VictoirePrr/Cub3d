#include "pars.h"

int	set_texture_filename(char **filename, char *token)
{
	char	*tmp;

	if (*filename)
		return (error_return("Duplicate texture"));
	tmp = ft_strtrim(token, " ./\t");
	if (!tmp)
		return (error_return("Error alloc"));
	*filename = ft_strdup(tmp);
	free(tmp);
	if (!*filename)
		return (error_return("Error alloc"));
	return (0);
}

int	parse_texture(char **tokens, t_game *game)
{
	if (ft_strcmp(tokens[0], "NO") == 0)
		return (set_texture_filename(&game->north->filename, tokens[1]));
	else if (ft_strcmp(tokens[0], "SO") == 0)
		return (set_texture_filename(&game->south->filename, tokens[1]));
	else if (ft_strcmp(tokens[0], "WE") == 0)
		return (set_texture_filename(&game->west->filename, tokens[1]));
	else if (ft_strcmp(tokens[0], "EA") == 0)
		return (set_texture_filename(&game->east->filename, tokens[1]));
	return (0);
}

int	parse_color_config(char **tokens, t_game *game)
{
	if (ft_strcmp(tokens[0], "F") == 0)
		return (parse_color_secure(tokens[1], game->floor, game));
	else if (ft_strcmp(tokens[0], "C") == 0)
		return (parse_color_secure(tokens[1], game->roof, game));
	return (error_return("Unknown configuration identifier"));
}

char	**split_tokens(char const *s)
{
	char	**result;
	int		i;
	int		size;

	if (*s == '\0')
		return (NULL);
	result = (char **)malloc(sizeof(char *) * 3);
	if (!result)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != ' ' && s[i] != '\t')
		i++;
	size = i;
	i = 0;
	result[0] = ft_tokndup(s, &i, size);
	size = ft_strlen(s);
	result[1] = ft_tokndup(s, &i, size);
	result[2] = NULL;
	return (result);
}

int	parse_config_secure(char *line, t_game *game)
{
	char	**tokens;
	char	*trimmed;
	int		result;

	trimmed = ft_strtrim(line, " \t\n");
	if (!trimmed)
		return (error_return("Memory allocation failed"));
	tokens = split_tokens(trimmed);
	free(trimmed);
	if (!tokens || !tokens[0] || !tokens[1])
	{
		free_split(tokens);
		return (error_return("Invalid configuration line"));
	}
	if (ft_strcmp(tokens[0], "F") == 0 || ft_strcmp(tokens[0], "C") == 0)
		result = parse_color_config(tokens, game);
	else
		result = parse_texture(tokens, game);
	free_split(tokens);
	return (result);
}

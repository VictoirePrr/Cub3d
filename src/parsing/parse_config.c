#include "pars.h"

int	parse_texture(char **tokens, t_game *game)
{
	char	*tmp;

	if (ft_strcmp(tokens[0], "NO") == 0)
	{
		if (game->north->filename)
			return (error_return("Duplicate north texture"));
		tmp = ft_strtrim(tokens[1], " ./");
		game->north->filename = ft_strdup(tmp);
		free(tmp);
	}
	else if (ft_strcmp(tokens[0], "SO") == 0)
	{
		if (game->south->filename)
			return (error_return("Duplicate south texture"));
		tmp = ft_strtrim(tokens[1], " ./");
		game->south->filename = ft_strdup(tmp);
		free(tmp);
	}
	else if (ft_strcmp(tokens[0], "WE") == 0)
	{
		if (game->west->filename)
			return (error_return("Duplicate west texture"));
		tmp = ft_strtrim(tokens[1], " ./");
		game->west->filename = ft_strdup(tmp);
		free(tmp);
	}
	else if (ft_strcmp(tokens[0], "EA") == 0)
	{
		if (game->east->filename)
			return (error_return("Duplicate east texture"));
		tmp = ft_strtrim(tokens[1], " ./");
		game->east->filename = ft_strdup(tmp);
		free(tmp);
	}
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
	// ALWAYS A SIZE OF 3 NO MATTER WHAT,
	// OTHERWISE YOU WOULD NOT BE IN THIS FUNCTION.
	if (!result)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != ' ' && s[i] != '\t')
		i++;
	// GET THE NAME OF THE TOKEN (ALWAYS SEPARATED BY A WHITESPACE FROM THE OTHER PART,
	// EX : F).
	size = i;
	i = 0;
	result[0] = ft_tokndup(s, &i, size); // TOKEN[0] HAS NOW THE NAME SEPARATED.
	size = ft_strlen(s);
	result[1] = ft_tokndup(s, &i, size);
	// GET ALL THE INFORMATIONS IN TOKEN[1], RAW. (EX : 156,17, 158).
	// WHY RAW ? WHITESPACES ARE NOT A PROBLEM FOR NOW,
	// ATOI WILL HANDLE THEM LATER.
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

int	validate_config_secure(t_game *game)
{
	if (!game->north->filename || !game->south->filename
		|| !game->west->filename || !game->east->filename)
		return (error_return("Missing texture(s)"));
	if (game->floor->r == -1 || game->roof->r == -1)
		return (error_return("Missing color(s)"));
	return (0);
}

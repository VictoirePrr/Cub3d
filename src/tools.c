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

void parse_map(char *line)
{
	(void)line;
	return ;
}
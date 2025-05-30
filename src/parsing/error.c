#include "pars.h"

int	print_error(char *str)
{
	ft_printf("Error: %s\n", str);
	return (1);
}

int	exit_error_cleanup(t_game *game, char *str, int fd) //useless
{
	print_error(str);
	if (fd > 0)
		close(fd);
	cleanup_game(game);
	return (1);
}

int	exit_error(t_game *game, char *str) //useless
{
	return (exit_error_cleanup(game, str, -1));
}

int	error_return(char *str)
{
	print_error(str);
	return (1);
}

int	error_return_line(char *str, char *line, int fd)
{
	print_error(str);
	if (line)
		free(line);
	if (fd > 0)
		close(fd);
	return (1);
}

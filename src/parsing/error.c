#include "pars.h"

int	print_error(char *str)
{
	ft_printf("Error: %s\n", str);
	return (1);
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

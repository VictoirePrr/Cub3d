/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pn <pn@student.42lyon.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 17:08:57 by pn                #+#    #+#             */
/*   Updated: 2025/07/23 17:08:58 by pn               ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

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

#include "cub3d.h"

char	**fill_the_matrix(const char *file, t_matrix *matrix)
{
	int		fd;
	char	*temp;

	temp = NULL;
	matrix->vtl = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (NULL);
	temp = get_next_line(fd);
	while (temp != NULL)
	{
		matrix->map[matrix->vtl] = dup_temp(temp);
		free(temp);
		if (!matrix->map[matrix->vtl])
			return (close(fd), NULL);
		matrix->vtl++;
		temp = get_next_line(fd);
	}
	free(temp);
	close(fd);
	return (matrix->map);
}

char	**read_map(const char *file, t_matrix *matrix)
{
	int		fd;
	char	*temp;

	temp = NULL;
	matrix->vtl = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (NULL);
	temp = get_next_line(fd);
	while (temp != NULL)
	{
		matrix->vtl++;
		free(temp);
		temp = NULL;
		temp = get_next_line(fd);
	}
	close(fd);
	matrix->map = calloc((matrix->vtl + 1), sizeof(char *));
	if (!matrix->map)
		return (NULL);
	if (!fill_the_matrix(file, matrix))
		return (free_all(matrix->map), NULL);
	matrix->vtl = 0;
	while (matrix->map[matrix->vtl])
	{
		matrix->htl = 0;
		while (matrix->map[matrix->vtl][matrix->htl])
			matrix->htl++;
		matrix->vtl++;
	}
	return (matrix->map);
}

t_img	put_xpm_to_img(void *xvar, char *xpm, t_img *img)
{
	if (ft_strcmp(xpm, PLAYER_XPM) == 0)
	{
		img->width = 16;
		img->height = 16;
	}
	else
	{
		img->width = XPM_WIDTH;
		img->height = XPM_HEIGHT;
	}
	img->image = mlx_xpm_file_to_image(xvar, xpm, &img->width, &img->height);
	if (!img->image)
		ft_printf("The image couldn't be initialized !\n");
	return (*img);
}

void	init_img(t_data *data, t_img *img)
{
	data->wall.image = NULL;
	data->floor.image = NULL;
	data->img_player.image = NULL;
	data->wall = put_xpm_to_img(data->mlx, WALL_XPM, img);
	if (!(data->wall.image))
		closing_game(data);
	data->floor = put_xpm_to_img(data->mlx, FLOOR_XPM, img);
	if (!(data->floor.image))
		closing_game(data);
	data->img_player = put_xpm_to_img(data->mlx, PLAYER_XPM, img);
	if (!(data->img_player.image))
		closing_game(data);
	set_up_game(data);
}

void	set_up_game(t_data *data)
{
	size_t	y;
	size_t	x;

	y = 0;
	while (data->matrix.map[y])
	{
		x = 0;
		while (data->matrix.map[y][x])
		{
			render_img(data, y, x);
			x++;
		}
		y++;
	}
}

void	render_img(t_data *data, int vtl, int htl)
{
	if (data->matrix.map[vtl][htl] == FLOOR)
		put_img_to_window(data, data->floor, vtl, htl);
	else if (data->matrix.map[vtl][htl] == WALL)
		put_img_to_window(data, data->wall, vtl, htl);
	else if (ft_strchr(PLAYER, data->matrix.map[vtl][htl]))
		put_img_to_window(data, data->floor, vtl, htl);
}


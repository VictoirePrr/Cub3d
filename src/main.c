#include "cub3d.h"

void	free_all(char **matrix)
{
	int	i;

	i = 0;
	if (!matrix)
		return ;
	while (matrix[i])
	{
		free(matrix[i]);
		matrix[i] = NULL;
		i++;
	}
	free(matrix);
	matrix = NULL;
}

char	*dup_temp(const char *s1)
{
	size_t	size;
	char	*dup;
	size_t	i;
	size_t	j;

	if (!s1)
		return (0);
	size = ft_strlen(s1) + 1;
	dup = calloc(size, sizeof(char));
	i = 0;
	j = 0;
	if (!(dup))
		return (0);
	while (s1[i])
	{
		if (s1[i] != '\n')
		{
			dup[j] = s1[i];
			j++;
		}
		i++;
	}
	return (dup);
}

int	closing_game(t_data *data)
{
	if (data)
	{
		if (data->wall.image)
			mlx_destroy_image(data->win, data->wall.image);
		if (data->floor.image)
			mlx_destroy_image(data->win, data->floor.image);
		if (data->matrix.map)
			free_all(data->matrix.map);
		if (data->mlx && data->win)
			mlx_destroy_window(data->mlx, data->win);
		if (data->mlx)
		{
			mlx_destroy_display(data->mlx);
			free(data->mlx);
		}
	}
	ft_printf("Game closed\n");
	exit(0);
}

void	put_img_to_window(t_data *data, t_img img, int vtl, int htl)
{
	mlx_put_image_to_window(data->mlx, data->win, img.image, htl * img.width,
		vtl * img.height);
}

void	render_img(t_data *data, int vtl, int htl)
{
	if (data->matrix.map[vtl][htl] == FLOOR)
		put_img_to_window(data, data->floor, vtl, htl);
	else if (data->matrix.map[vtl][htl] == WALL)
		put_img_to_window(data, data->wall, vtl, htl);
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
	// play_game(data);
}

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

void	update_player_pos(t_data *data, int color)
{
	int	x;
	int	player_size;
	int	y;
	int	new_x;
	int	new_y;

	new_x = data->start_x;
	new_y = data->start_y;
	player_size = 10;
	y = 0;
	while (y < player_size)
	{
		x = 0;
		while (x < player_size)
		{
			mlx_pixel_put(data->mlx, data->win, new_x + x, new_y + y, color);
			x++;
		}
		y++;
	}
}

int	get_key(int key, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (key == UP || key == W)
	{
		update_player_pos(data, 0x000000);
		data->start_y -= 1;
		update_player_pos(data, 0x00FF00);
	}
	else if (key == DOWN || key == S)
	{
		update_player_pos(data, 0x000000);
		data->start_y += 1;
		update_player_pos(data, 0x00FF00);
	}
	else if (key == LEFT || key == A)
	{
		update_player_pos(data, 0x000000);
		data->start_x -= 1;
		update_player_pos(data, 0x00FF00);
	}
	else if (key == RIGHT || key == D)
	{
		update_player_pos(data, 0x000000);
		data->start_x += 1;
		update_player_pos(data, 0x00FF00);
	}
	return (0);
}

void	draw_player(t_data *data)
{
	int	x;
	int	player_size;
	int	y;

	player_size = 10;
	x = 0;
	while (x < player_size)
	{
		y = 0;
		while (y < player_size)
		{
			mlx_pixel_put(data->mlx, data->win, data->start_x + x, data->start_y
				+ y, 0x00FF00);
			y++;
		}
		x++;
	}
}

t_img	put_xpm_to_win(void *xvar, char *xpm, t_img *img)
{
	img->width = XPM_WIDTH;
	img->height = XPM_HEIGHT;
	img->image = mlx_xpm_file_to_image(xvar, xpm, &img->width, &img->height);
	if (!img->image)
		ft_printf("The image couldn't be initialized !\n");
	return (*img);
}

void	init_img(t_data *data, t_img *img)
{
	data->wall.image = NULL;
	data->floor.image = NULL;
	data->wall = put_xpm_to_win(data->mlx, WALL_XPM, img);
	if (!(data->wall.image))
		closing_game(data);
	data->floor = put_xpm_to_win(data->mlx, FLOOR_XPM, img);
	if (!(data->floor.image))
		closing_game(data);
	set_up_game(data);
}

void	open_window(t_data *data, t_img *img, char *map)
{
	data->matrix.map = read_map(map, &data->matrix);
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, XPM_HEIGHT * (data->matrix.htl),
			XPM_WIDTH * (data->matrix.vtl), "Empty window");
	// data->start_x = 200;
	// data->start_y = 200;
	// draw_player(data);
	init_img(data, img);
	mlx_key_hook(data->win, get_key, data);
	mlx_hook(data->win, 17, 0, closing_game, data);
	mlx_loop(data->mlx);
}

int	main(int argc, char **argv)
{
	t_data	data;
	t_img	img;

	(void)argc;
	(void)argv;
	open_window(&data, &img, argv[1]);
	// data.start_x = 200;
	// data.start_y = 200;
	// data.matrix.map = read_map(argv[1], &data.matrix);
	// init_img(&data, &img);
	// draw_player(&data);
	// mlx_key_hook(&data.win, get_key, &data);
	// mlx_hook(&data.win, 17, 0, closing_game, &data);
	// mlx_loop(&data.mlx);
	return (0);
}

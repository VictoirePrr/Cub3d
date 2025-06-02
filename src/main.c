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

int	closing_game(t_data *data)
{
	if (data->wall.image)
		mlx_destroy_image(data->mlx, data->wall.image);
	if (data->floor.image)
		mlx_destroy_image(data->mlx, data->floor.image);
	if (data->img_player.image)
		mlx_destroy_image(data->mlx, data->img_player.image);
	if (data->matrix.map)
		free_all(data->matrix.map);
	if (data->mlx && data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
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
	else if (ft_strchr(PLAYER, data->matrix.map[vtl][htl]))
		put_img_to_window(data, data->floor, vtl, htl);
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


void	move_forward(t_data *data)
{
	float	new_x = data->player.x + data->player.dir_x * 1;
	float	new_y = data->player.y + data->player.dir_y * 1;

	// Check collisions
	if (data->matrix.map[(int)new_y][(int)new_x] != '1')
	{
		data->player.x = new_x;
		data->player.y = new_y;
	}
}

void	move_backward(t_data *data)
{
	float	new_x = data->player.x - data->player.dir_x * 1;
	float	new_y = data->player.y - data->player.dir_y * 1;

	if (data->matrix.map[(int)new_y][(int)new_x] != '1')
	{
		data->player.x = new_x;
		data->player.y = new_y;
	}
}

void	move_left(t_data *data)
{
	float	new_x = data->player.x - data->player.dir_x * 1;
	float	new_y = data->player.y - data->player.dir_y * 1;

	if (data->matrix.map[(int)new_y][(int)new_x] != '1')
	{
		data->player.x = new_x;
		data->player.y = new_y;
	}
}


int	key_press(int key, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (key == ESC)
		closing_game(data);
	else if (key == UP || key == W)
		data->player.move_forward = 1;
	else if (key == DOWN || key == S)
		data->player.move_backward = 1;
	else if (key == A)
		data->player.move_left = 1;
	else if (key == D)
		data->player.move_right = 1;
	else if (key == LEFT)
		data->player.rotate_left = 1;
	else if (key == RIGHT)
		data->player.rotate_right = 1;
	return (0);
}

int	key_release(int key, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (key == UP || key == W)
		data->player.move_forward = 0;
	else if (key == DOWN || key == S)
		data->player.move_backward = 0;
	else if (key == A)
		data->player.move_left = 0;
	else if (key == D)
		data->player.move_right = 0;
	else if (key == LEFT)
		data->player.rotate_left = 0;
	else if (key == RIGHT)
		data->player.rotate_right = 0;
	return (0);
}

int	update_player_pos(t_data *data)
{
	if (data->player.move_forward)
		move_forward(data);
	if (data->player.move_backward)
		move_backward(data);
	if (data->player.move_left)
		move_left(data);
	if (data->player.move_right)
		move_right(data);
	if (data->player.rotate_left)
		rotate_left(data);
	if (data->player.rotate_right)
		rotate_right(data);
}

void	set_dir(char *c, t_data *data)
{
	if (c[0] == 'N')
	{
		data->player.dir_x = 0;
		data->player.dir_y = -1;
	}
	else if (c[0] == 'S')
	{
		data->player.dir_x = 0;
		data->player.dir_y = 1;
	}
	else if (c[0] == 'E')
	{
		data->player.dir_x = 1;
		data->player.dir_y = 0;
	}
	else if (c[0] == 'W')
	{
		data->player.dir_x = -1;
		data->player.dir_y = 0;
	}
}

void	draw_player(t_data *data)
{
	size_t	y;
	size_t	x;

	y = 0;
	while (data->matrix.map[y])
	{
		x = 0;
		while (data->matrix.map[y][x])
		{
			if (ft_strchr(PLAYER, data->matrix.map[y][x]))
			{
				data->player.x = x;
				data->player.y = y;
				set_dir(ft_strchr(PLAYER, data->matrix.map[y][x]), data);
				put_img_to_window(data, data->floor, y, x);
				put_img_to_window(data, data->img_player, y, x);
			}
			x++;
		}
		y++;
	}
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

void	open_window(t_data *data, t_img *img, char *map)
{
	data->matrix.map = read_map(map, &data->matrix);
	if (!data->matrix.map)
		closing_game(data);
	if (data->matrix.vtl == 0 || data->matrix.htl == 0)
	{
		ft_printf("Map is empty or invalid\n");
		closing_game(data);
	}
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, XPM_HEIGHT * (data->matrix.htl),
			XPM_WIDTH * (data->matrix.vtl), "Minimap");
	init_img(data, img);
	draw_player(data);
	// init data keys before release or press....
	data->keys.up = 0;
	data->keys.down = 0;
	data->keys.left = 0;
	data->keys.right = 0;
	mlx_hook(data->win, 2, 1L << 0, key_press, data);
	mlx_hook(data->win, 3, 1L << 1, key_release, data);
	mlx_loop_hook(data->mlx, update_player_pos, data);
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

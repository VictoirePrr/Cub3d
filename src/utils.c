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

void	put_img_to_window(t_data *data, t_img img, int vtl, int htl)
{
	mlx_put_image_to_window(data->mlx, data->win, img.image, htl * img.width,
		vtl * img.height);
}
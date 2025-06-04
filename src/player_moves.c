#include "cub3d.h"

void	move_forward(t_data *data)
{
	float	new_x;
	float	new_y;

	new_x = data->player.x + data->player.dir_x * MOVE_SPEED;
	new_y = data->player.y + data->player.dir_y * MOVE_SPEED;
	if (data->matrix.map[(int)new_y][(int)new_x] != '1')
	{
		data->player.x = new_x;
		data->player.y = new_y;
	}
}

void	move_backward(t_data *data)
{
	float	new_x;
	float	new_y;

	new_x = data->player.x - data->player.dir_x * MOVE_SPEED;
	new_y = data->player.y - data->player.dir_y * MOVE_SPEED;
	if (data->matrix.map[(int)new_y][(int)new_x] != '1')
	{
		data->player.x = new_x;
		data->player.y = new_y;
	}
}

void	move_left(t_data *data)
{
	float	strafe_x;
	float	strafe_y;
	float	new_x;
	float	new_y;

	strafe_x = -data->player.dir_y;
	strafe_y = data->player.dir_x;
	new_x = data->player.x + strafe_x * MOVE_SPEED;
	new_y = data->player.y + strafe_y * MOVE_SPEED;
	if (data->matrix.map[(int)new_y][(int)new_x] != '1')
	{
		data->player.x = new_x;
		data->player.y = new_y;
	}
}

void	move_right(t_data *data)
{
	float	strafe_x;
	float	strafe_y;
	float	new_x;
	float	new_y;

	strafe_x = data->player.dir_y;
	strafe_y = -data->player.dir_x;
	new_x = data->player.x + strafe_x * MOVE_SPEED;
	new_y = data->player.y + strafe_y * MOVE_SPEED;
	if (data->matrix.map[(int)new_y][(int)new_x] != '1')
	{
		data->player.x = new_x;
		data->player.y = new_y;
	}
}

void	rotate_left(t_data *data)
{
	double	old_dir_x;
	double	angle;

	old_dir_x = data->player.dir_x;
	angle = ROTATE_SPEED;
	data->player.dir_x = data->player.dir_x * cos(angle) - data->player.dir_y
		* sin(angle);
	data->player.dir_y = old_dir_x * sin(angle) + data->player.dir_y
		* cos(angle);
	// // If you have a camera plane (for raycasting):
	// double old_plane_x = data->player.plane_x;
	// data->player.plane_x = data->player.plane_x * cos(angle)
	// 	- data->player.plane_y * sin(angle);
	// // data->player.plane_y = old_plane_x * sin(angle) + data->player.plane_y
	// 	* cos(angle);
}

void	rotate_right(t_data *data)
{
	double old_dir_x = data->player.dir_x;
	double angle = -ROTATE_SPEED;

	data->player.dir_x = data->player.dir_x * cos(angle) - data->player.dir_y
		* sin(angle);
	data->player.dir_y = old_dir_x * sin(angle) + data->player.dir_y
		* cos(angle);

	// double old_plane_x = data->player.plane_x;
	// data->player.plane_x = data->player.plane_x * cos(angle)
	// 	- data->player.plane_y * sin(angle);
	// // data->player.plane_y = old_plane_x * sin(angle) + data->player.plane_y
	// 	* cos(angle);
}
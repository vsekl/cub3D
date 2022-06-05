#include "../includes/executor.h"
#include <float.h>  

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

t_ray	*shortest_ray(t_ray *ray_1, t_ray *ray_2)
{
	if (ray_1->dist < ray_2->dist)
		return ray_1;
	return ray_2;
}

t_ray *ray(double dist, int type)
{
	t_ray *ray;

	ray = malloc(sizeof(t_ray));
	ray->dist = dist;
	ray->type = type;
	return (ray);
}

double horizontal_inter(double pos_x, double pos_y, double angle, int texture_size, char **map)
{
	double inter_x;
	double inter_y;

	double delta_x;
	double delta_y;

	double max_x= texture_size * 10;
	if (angle <= 180)
	{
		inter_y = (int)(pos_y / texture_size) * texture_size - 1;
		delta_y = -texture_size; 
	}
	else
	{
		inter_y = (int)(pos_y / texture_size) * texture_size + texture_size;
		delta_y = texture_size; 
	}
	inter_x = pos_x + (pos_y - inter_y) / tan(angle * PI_TO_RAD);
	delta_x = texture_size / tan(angle * PI_TO_RAD);
	while(inter_x <= max_x && inter_x >= 0)
	{
		int x = inter_x / texture_size;
		int y = inter_y / texture_size;
		if (map[y][x] == '1')
			return (sqrt((pos_x - inter_x)*(pos_x - inter_x) + (pos_y - inter_y)*(pos_y - inter_y)));
		inter_x+=delta_x;
		inter_y+=delta_y;
	}
	return (DBL_MAX);
}

double vertical_inter(double pos_x, double pos_y, double angle, int texture_size, char **map)
{
	double inter_x;
	double inter_y;

	double delta_x;
	double delta_y;

	double max_y= texture_size * 10;

	if (angle <= 90 || angle >= 270)
	{
		inter_x = (int)(pos_x / texture_size) * texture_size + texture_size;
		delta_x = texture_size;
	}
	else
	{
		inter_x = (int)(pos_x / texture_size) * texture_size -1;
		delta_x = -texture_size;
	}
	inter_y = pos_y + (pos_x - inter_x) * tan(angle * PI_TO_RAD);
	delta_y = texture_size * tan(angle * PI_TO_RAD);
	 
	while(inter_y <= max_y && inter_y >= 0)
	{
		int x = inter_x / texture_size;
		int y = inter_y / texture_size;
		if (map[y][x] == '1')
			return (sqrt((pos_x - inter_x)*(pos_x - inter_x) + (pos_y - inter_y)*(pos_y - inter_y)));
		inter_x+=delta_x;
		inter_y+=delta_y;
	}
	return (DBL_MAX);
}

double min(double x1, double x2)
{
	if (x1 < x2)
		return x1;
	return x2;
}

int find_texture_type(double angle)
{	
	if (angle < 0)
		angle= 360 + angle;
	if (angle <= 90)
		return 0xFF0000;
	else if (angle <= 180)
		return 0x0000FF;
	else if (angle <= 270)
		return 0x00FF00;
	else
		return 0xFFFF00;
}
// 0xFF0000 RED
// 0x0000FF BLUE
// 0x00FF00 GREEN
// 0xFFFF00 YELLOW
void render(t_game *game)
{
	double wall_height;
	double angle;
	int rays;
	double dist;
	t_data img;
	img.img = mlx_new_image(game->mlx, game->plane_width, game->plane_height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	angle = game->player.pov - game->fov/2.0;
	rays = game->plane_width;

	while (rays--)
	{
		// angle= fmod(angle, 360);
		// if (angle < 0)
		// 	angle= angle + 360;
		dist= min(horizontal_inter(game->player.x, game->player.y, angle, game->texture_size, game->map), 
		  				vertical_inter(game->player.x, game->player.y, angle, game->texture_size, game->map));
		int type = find_texture_type(angle);
		dist *= cos((game->fov/2  - (game->plane_width - rays) * game->delta_angle)  * PI_TO_RAD );
		printf("dist=%f\n",dist);
		wall_height = (game->texture_size / dist * game->dist_to_plane);
		wall_height = (int)(wall_height) + 1;
		for(int i = 0 ; i <= wall_height; i++)
				my_mlx_pixel_put(&img,  rays, (game->plane_height / 2 - (wall_height / 2)) + i, type);		
		mlx_put_image_to_window(game->mlx, game->win, img.img, 0, 0);
		angle+= game->delta_angle;
	}
}
int	key_hook(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		exit(1);
	else if (keycode == KEY_W)
	{
		double next_x = game->player.x + game->player.step_length * cos(game->player.pov  * PI_TO_RAD);
		double next_y = game->player.y - game->player.step_length * sin(game->player.pov * PI_TO_RAD);
		if (next_x >= game->texture_size && next_y >= game->texture_size && 1 && 1)
		{
			game->player.x = next_x;
			game->player.y = next_y;
		}
	}
	else if (keycode == KEY_A)
		game->player.pov+=5;
	else if (keycode == KEY_S)
	{
		game->player.x-= game->player.step_length * cos(game->player.pov  * PI_TO_RAD);
		game->player.y+= game->player.step_length * sin(game->player.pov * PI_TO_RAD);
	}
	else if (keycode == KEY_D)
		game->player.pov-=5;
	
	game->player.pov= fmod(game->player.pov, 360);
	if (game->player.pov < 0)
		game->player.pov= game->player.pov + 360;
	render(game);
	printf("pov = %f\nx=%f  y= %f\n",game->player.pov, game->player.x,game->player.y);
	return (0);
}

int main()
{
	t_game game;
	init_game(&game);
	render(&game);
	mlx_key_hook(game.win, key_hook, &game);
	mlx_loop(game.mlx);
}







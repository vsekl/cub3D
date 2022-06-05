#ifndef EXECUTOR_H
# define EXECUTOR_H

# include <unistd.h>
# include "../libft/libft.h"
# include <stdlib.h>
# include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
# include <mlx.h>
#include <math.h>

# define KEY_ESC 53
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define PI_TO_RAD 0.017453
typedef struct s_ray
{
	double dist;
	int type;
}t_ray;

typedef struct	s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}t_data;

typedef struct s_player
{
	double x;
	double y;
	double pov;
	double step_length;
}t_player;

typedef struct s_game
{
	void	*mlx;
	void	*win;
	char	**map;
	t_player player;
	int 	texture_size;
	double plane_width;
	double plane_height;
	double dist_to_plane;
	double fov;
	double delta_angle;
	t_data wall;
}t_game;

void	init_game(t_game *game);
char 	**parse_map();

#endif
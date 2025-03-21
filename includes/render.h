/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcheron <jcheron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 16:00:22 by edetoh            #+#    #+#             */
/*   Updated: 2025/03/21 08:03:45 by jcheron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "cub.h"

typedef struct s_ray
{
	double	x;
	double	y;
	double	cos_angle;
	double	sin_angle;
	double	delta_dist_x;
	double	delta_dist_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	int		step_x;
	int		step_y;
	int		side;
	bool	hit;
}	t_ray;

typedef struct s_wall
{
	double			dist;
	double			perp_dist;
	mlx_texture_t	*texture;
	double			x;
	int				height;
	int				start;
	int				end;
	int				tex_x;
	double			step;
	double			cos_angle;
	double			sin_angle;
	int				side;
}	t_wall;

typedef struct s_point
{
	double	x;
	double	y;
}	t_point;

typedef struct s_pixel
{
	int			x;
	int			y;
	uint8_t		*color;
	double		dist;
}	t_pixel;

// Draw utilities
int		get_rgba(int r, int g, int b, int a);
void	clear_image(t_game *game);
double	ft_clamp(double value, double min, double max);

// Background drawing
void	draw_background(t_game *game);

// Ray utilities
double	distance(float x, float y);
bool	touch(double px, double py, t_game *game);
double	fixed_dist(t_point start, t_point end, t_game *game);

// Ray casting
void	init_ray(t_ray *ray, double fx, t_game *game);
void	calculate_step(t_ray *ray);
void	detect_wall(t_ray *ray, t_game *game);
void	draw_wall_line(t_ray *ray, t_game *game, int i, double fx);

// Ray drawing
void	calculate_wall_params(t_ray *ray, t_game *game,
			double fx, t_wall *wall);
void	draw_textured_line(t_game *game, t_wall *wall, int x);
void	draw_pixel(t_game *game, t_pixel pixel);

#endif

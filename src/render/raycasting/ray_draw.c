/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edetoh <edetoh@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 16:00:22 by edetoh            #+#    #+#             */
/*   Updated: 2025/03/03 13:26:30 by edetoh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub.h"
#include "../../../includes/render.h"

/**
 * @brief 🎨 Configure la texture et la distance du mur
 * @param ray Pointeur vers les paramètres du rayon
 * @param game Pointeur vers la structure du jeu
 * @param wall Pointeur vers les paramètres du mur
 */
static void	set_wall_texture_and_dist(t_ray *ray, t_game *game, t_wall *wall)
{
	if (ray->side == 0)
	{
		wall->dist = (ray->side_dist_x - ray->delta_dist_x * BLOCK_SIZE);
		if (ray->cos_angle > 0)
			wall->texture = game->texture_north;
		else
			wall->texture = game->texture_south;
		wall->x = ray->y + wall->dist * ray->sin_angle;
	}
	else
	{
		wall->dist = (ray->side_dist_y - ray->delta_dist_y * BLOCK_SIZE);
		if (ray->sin_angle > 0)
			wall->texture = game->texture_east;
		else
			wall->texture = game->texture_west;
		wall->x = ray->x + wall->dist * ray->cos_angle;
	}
}

/**
 * @brief 📏 Calcule les dimensions du mur
 * @param wall Pointeur vers les paramètres du mur
 * @param fx Angle du rayon
 * @param game Pointeur vers la structure du jeu
 */
static void	calculate_wall_dimensions(t_wall *wall, double fx, t_game *game)
{
	wall->x = wall->x - floor(wall->x / BLOCK_SIZE) * BLOCK_SIZE;
	wall->perp_dist = wall->dist * cos(fx - game->player.angle);
	wall->height = (int)(WINDOW_HEIGHT / wall->perp_dist * BLOCK_SIZE);
	wall->start = -wall->height / 2 + WINDOW_HEIGHT / 2;
	wall->end = wall->height / 2 + WINDOW_HEIGHT / 2;
}

/**
 * @brief 📐 Calcule les paramètres du mur pour le rendu
 * @param ray Pointeur vers les paramètres du rayon
 * @param game Pointeur vers la structure du jeu
 * @param fx Angle du rayon
 * @param wall Pointeur vers les paramètres du mur
 */
void	calculate_wall_params(t_ray *ray, t_game *game, double fx, t_wall *wall)
{
	set_wall_texture_and_dist(ray, game, wall);
	calculate_wall_dimensions(wall, fx, game);
	if (wall->start < 0)
		wall->start = 0;
	if (wall->end >= WINDOW_HEIGHT)
		wall->end = WINDOW_HEIGHT - 1;
}

/**
 * @brief 🎨 Draws a textured vertical line
 * @param game Pointer to game structure
 * @param wall Pointer to wall parameters
 * @param x Screen x coordinate to draw at
 */
void	draw_textured_line(t_game *game, t_wall *wall, int x)
{
	int		y;
	double	tex_pos;
	int		tex_y;
	t_pixel	pixel;

	wall->tex_x = (int)(wall->x * wall->texture->width / BLOCK_SIZE);
	if ((wall->side == 0 && wall->cos_angle > 0) || \
		(wall->side == 1 && wall->sin_angle < 0))
		wall->tex_x = wall->texture->width - wall->tex_x - 1;
	wall->tex_x = ft_clamp(wall->tex_x, 0, wall->texture->width - 1);
	wall->step = (double)wall->texture->height / wall->height;
	tex_pos = (wall->start - WINDOW_HEIGHT / 2 + wall->height / 2) * wall->step;
	y = wall->start;
	while (y <= wall->end)
	{
		tex_y = (int)tex_pos & (wall->texture->height - 1);
		pixel.x = x;
		pixel.y = y;
		pixel.color = &wall->texture->pixels[(tex_y * wall->texture->width + \
			wall->tex_x) * wall->texture->bytes_per_pixel];
		pixel.dist = wall->perp_dist;
		draw_pixel(game, pixel);
		tex_pos += wall->step;
		y++;
	}
}

/**
 * @brief 🖌️ Draws a single pixel with shading
 * @param game Pointer to game structure
 * @param pixel Pixel parameters structure
 */
void	draw_pixel(t_game *game, t_pixel pixel)
{
	double	shade;
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	uint8_t	a;

	shade = ft_clamp(1.0 - (pixel.dist / (WINDOW_WIDTH * 0.7)), 0.3, 1.0);
	r = (uint8_t)(pixel.color[0] * shade);
	g = (uint8_t)(pixel.color[1] * shade);
	b = (uint8_t)(pixel.color[2] * shade);
	a = pixel.color[3];
	mlx_put_pixel(game->image_global, pixel.x, pixel.y, get_rgba(r, g, b, a));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edetoh <edetoh@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 16:00:22 by edetoh            #+#    #+#             */
/*   Updated: 2025/02/28 16:23:12 by edetoh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub.h"

int get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
};

int load_textures(t_game *game)
{
	// Chargement texture Nord
	game->texture_north = mlx_load_png("src/render/assets/wolftextures1.png");
	if (!game->texture_north)
		return (0);

	// Chargement texture Sud
	game->texture_south = mlx_load_png("src/render/assets/wolftextures2.png");
	if (!game->texture_south)
	{
		mlx_delete_texture(game->texture_north);
		return (0);
	}

	// Chargement texture Est
	game->texture_east = mlx_load_png("src/render/assets/wolftextures3.png");
	if (!game->texture_east)
	{
		mlx_delete_texture(game->texture_north);
		mlx_delete_texture(game->texture_south);
		return (0);
	}

	// Chargement texture Ouest
	game->texture_west = mlx_load_png("src/render/assets/wolftextures4.png");
	if (!game->texture_west)
	{
		mlx_delete_texture(game->texture_north);
		mlx_delete_texture(game->texture_south);
		mlx_delete_texture(game->texture_east);
		return (0);
	}

	return (1);
}

void draw_square(int x, int y, int size, int color, t_game *game)
{
	int i;

	i = 0;
	while (i < size)
	{
		mlx_put_pixel(game->image_global, x + i, y, color);
		i++;
	}
	i = 0;
	while (i < size)
	{
		mlx_put_pixel(game->image_global, x, y + i, color);
		i++;
	}
	i = 0;
	while (i < size)
	{
		mlx_put_pixel(game->image_global, x + size, y + i, color);
		i++;
	}
	i = 0;
	while (i < size)
	{
		mlx_put_pixel(game->image_global, x + i, y + size, color);
		i++;
	}
}

char **get_map(void)
{
	char **map = malloc(sizeof(char *) * 11);
	map[0] = ft_strdup("1111111111111111");
	map[1] = ft_strdup("1000000000000001");
	map[2] = ft_strdup("1000000000000001");
	map[3] = ft_strdup("1000000000000001");
	map[4] = ft_strdup("1000010000000001");
	map[5] = ft_strdup("1000000000000001");
	map[6] = ft_strdup("10000000000000011");
	map[7] = ft_strdup("1000000001100001");
	map[8] = ft_strdup("1000000000100001");
	map[9] = ft_strdup("1111111111111111");
	map[10] = NULL;
	return (map);
}

void clear_image(t_game *game)
{
	int x;
	int y;

	y = 0;
	while (y < WINDOW_HEIGHT) {
		x = 0;
		while (x < WINDOW_WIDTH) {
			mlx_put_pixel(game->image_global, x, y, get_rgba(0, 0, 0, 255));
			x++;
		}
		y++;
	}
}

void draw_map(t_game game) {
	char **map = game.map;

	int x;
	int y;

	y = 0;
	x = 0;

	while (map[y]) {
		x = 0;
		while (map[y][x]) {
			if (map[y][x] == '1') {
				draw_square(x * BLOCK_SIZE, y * BLOCK_SIZE, BLOCK_SIZE, get_rgba(50, 50, 255, 255), &game);
			}
			x++;
		}
		y++;
	}
}

double distance(float x, float y){
	return sqrtf(x * x + y * y);
}

bool touch(double px, double py, t_game *game) {
    int x = (int)(px / BLOCK_SIZE);
    int y = (int)(py / BLOCK_SIZE);

    // Vérification des limites de la carte
    if (x < 0 || y < 0 || !game->map[y] || !game->map[y][x])
        return true;

    return (game->map[y][x] == '1');
}

double fixed_dist(double x1, double y1, double x2, double y2, t_game *game) {

	double delta_x = x2 - x1;
	double delta_y = y2 - y1;
	double angle = atan2(delta_y, delta_x) - game->player.angle;
	double fix_dist = distance(delta_x, delta_y) * cos(angle);
	return (fix_dist);
}

double ft_clamp(double value, double min, double max)
{
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

void draw_line(t_game *game, double fx, int i)
{
    double ray_x = game->player.x;
    double ray_y = game->player.y;
    double cos_angle = cos(fx);
    double sin_angle = sin(fx);
    int side = 0;
    mlx_texture_t *texture;
    double wall_dist;
    int tex_x;

    // Calcul du DDA (Digital Differential Analyzer)
    double delta_dist_x = (cos_angle == 0) ? 1e30 : fabs(1.0 / cos_angle);
    double delta_dist_y = (sin_angle == 0) ? 1e30 : fabs(1.0 / sin_angle);

    int map_x = (int)(ray_x / BLOCK_SIZE);
    int map_y = (int)(ray_y / BLOCK_SIZE);

    double side_dist_x;
    double side_dist_y;
    int step_x;
    int step_y;

    // Calcul du pas et de la distance initiale
    if (cos_angle < 0)
    {
        step_x = -1;
        side_dist_x = (ray_x - map_x * BLOCK_SIZE) * delta_dist_x;
    }
    else
    {
        step_x = 1;
        side_dist_x = ((map_x + 1.0) * BLOCK_SIZE - ray_x) * delta_dist_x;
    }
    if (sin_angle < 0)
    {
        step_y = -1;
        side_dist_y = (ray_y - map_y * BLOCK_SIZE) * delta_dist_y;
    }
    else
    {
        step_y = 1;
        side_dist_y = ((map_y + 1.0) * BLOCK_SIZE - ray_y) * delta_dist_y;
    }

    // DDA
    bool hit = false;
    while (!hit)
    {
        if (side_dist_x < side_dist_y)
        {
            side_dist_x += delta_dist_x * BLOCK_SIZE;
            map_x += step_x;
            side = 0;
        }
        else
        {
            side_dist_y += delta_dist_y * BLOCK_SIZE;
            map_y += step_y;
            side = 1;
        }

        if (map_x < 0 || map_y < 0 || !game->map[map_y] || !game->map[map_y][map_x])
            break;

        if (game->map[map_y][map_x] == '1')
            hit = true;
    }

    // Calcul de la distance et de la hauteur du mur
    double wall_x;
    if (side == 0)
    {
        wall_dist = (side_dist_x - delta_dist_x * BLOCK_SIZE);
        texture = (cos_angle > 0) ? game->texture_north : game->texture_south;
        wall_x = ray_y + wall_dist * sin_angle;
        wall_x = wall_x - floor(wall_x / BLOCK_SIZE) * BLOCK_SIZE;
    }
    else
    {
        wall_dist = (side_dist_y - delta_dist_y * BLOCK_SIZE);
        texture = (sin_angle > 0) ? game->texture_east : game->texture_west;
        wall_x = ray_x + wall_dist * cos_angle;
        wall_x = wall_x - floor(wall_x / BLOCK_SIZE) * BLOCK_SIZE;
    }

    // Calcul des coordonnées de texture
    tex_x = (int)(wall_x * texture->width / BLOCK_SIZE);
    if ((side == 0 && cos_angle > 0) || (side == 1 && sin_angle < 0))
        tex_x = texture->width - tex_x - 1;
    tex_x = ft_clamp(tex_x, 0, texture->width - 1);

    // Calcul de la hauteur de la ligne
    double perp_wall_dist = wall_dist * cos(fx - game->player.angle);
    int line_height = (int)(WINDOW_HEIGHT / perp_wall_dist * BLOCK_SIZE);

    int draw_start = -line_height / 2 + WINDOW_HEIGHT / 2;
    if (draw_start < 0)
        draw_start = 0;
    int draw_end = line_height / 2 + WINDOW_HEIGHT / 2;
    if (draw_end >= WINDOW_HEIGHT)
        draw_end = WINDOW_HEIGHT - 1;

    // Rendu de la texture
    double step = (double)texture->height / line_height;
    double tex_pos = (draw_start - WINDOW_HEIGHT / 2 + line_height / 2) * step;

    for (int y = draw_start; y <= draw_end; y++)
    {
        int tex_y = (int)tex_pos & (texture->height - 1);
        uint8_t *pixel = &texture->pixels[(tex_y * texture->width + tex_x) * texture->bytes_per_pixel];

        double shade = ft_clamp(1.0 - (perp_wall_dist / (WINDOW_WIDTH * 0.7)), 0.3, 1.0);

        uint8_t r = (uint8_t)(pixel[0] * shade);
        uint8_t g = (uint8_t)(pixel[1] * shade);
        uint8_t b = (uint8_t)(pixel[2] * shade);
        uint8_t a = pixel[3];

        mlx_put_pixel(game->image_global, i, y, get_rgba(r, g, b, a));
        tex_pos += step;
    }
}

void draw_background(t_game *game)
{
	int x = 0;
	int y = 0;
	while (y < WINDOW_HEIGHT / 2) {
		x = 0;
		while (x < WINDOW_WIDTH) {
			mlx_put_pixel(game->image_global, x, y, get_rgba(120, 190, 255, 255));
			x++;
		}
		y++;
		}
	while (y < WINDOW_HEIGHT) {
		x = 0;
		while (x < WINDOW_WIDTH) {
			mlx_put_pixel(game->image_global, x, y, get_rgba(63, 155, 11, 255));
			x++;
			}
		y++;
		}
}

// void test_texture(t_game *game)
// {
// 	mlx_image_t *tex = game->texture_east;
// 	int start_x = (WINDOW_WIDTH - tex->width) / 2;
// 	int start_y = (WINDOW_HEIGHT - tex->height) / 2;
//
// 	// Debug: afficher les valeurs de pixels
// 	printf("Premier pixel: R:%d G:%d B:%d A:%d\n",
// 		(tex->pixels[0] >> 24) & 0xFF,
// 		(tex->pixels[0] >> 16) & 0xFF,
// 		(tex->pixels[0] >> 8) & 0xFF,
// 		tex->pixels[0] & 0xFF);
//
// 	// Copier la texture directement
// 	for (uint32_t y = 0; y < tex->height; y++) {
// 		for (uint32_t x = 0; x < tex->width; x++) {
// 			uint32_t color = tex->pixels[y * tex->width + x];
// 			// Inverser l'ordre des composantes RGB
// 			uint8_t r = (color >> 24) & 0xFF;
// 			uint8_t g = (color >> 16) & 0xFF;
// 			uint8_t b = (color >> 8) & 0xFF;
// 			uint8_t a = color & 0xFF;
//
// 			// Utiliser l'ordre correct pour MLX42
// 			uint32_t final_color = (r << 24) | (g << 16) | (b << 8) | a;
//
// 			if (start_x + x < WINDOW_WIDTH && start_y + y < WINDOW_HEIGHT)
// 				mlx_put_pixel(game->image_global, start_x + x, start_y + y, final_color);
// 		}
// 	}
// 	mlx_texture_to_image(game->mlx, game->texture_east->pixels);
// 	mlx_image_to_window(game->mlx, game->image_global, 0, 0);
// }


void draw_loop(void *param)
{
	static double x;
	static double y;
	static double angle;

	t_game* game = (t_game*)param;

	// t_player *player = &game->player;
	if (x != game->player.x || y != game->player.y	|| angle !=	game->player.angle) {
		clear_image(game);
		draw_background(game);
		// draw_map(*game);
		// draw_square(player->x, player->y, 5, get_rgba(255, 0, 0, 255), game);
		// draw_line(game, x, y);

	    double fraction = PI / 3 / WINDOW_WIDTH;
		double start_x = game->player.angle - PI / 6;
		int i = 0;
		while (i < WINDOW_WIDTH) {
			draw_line(game, start_x, i);
			start_x += fraction;
			i++;
		}
		// test_texture(game);
		mlx_image_to_window(game->mlx, game->image_global, 0, 0);
		x = game->player.x;
		y = game->player.y;
		angle = game->player.angle;

		//DEGUB
		printf("POSITION : %f %f\n", game->player.x, game->player.y);
		printf("ANGLE : %f\n", game->player.angle);
		//FIN DEBUB
	}
}


void init_game(t_game *game)
{
	init_player(&game->player);
	game->map = get_map();
	game->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3D", false);
	game->image_global = mlx_new_image(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!load_textures(game))
		error_exit("Failed to load textures");
	mlx_image_to_window(game->mlx, game->image_global, 0, 0);
}
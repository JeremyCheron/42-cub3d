/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edetoh <edetoh@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 16:00:22 by edetoh            #+#    #+#             */
/*   Updated: 2025/02/28 14:32:59 by edetoh           ###   ########.fr       */
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
	game->texture_north = mlx_load_png("src/render/assets/wolftextures2.png");
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
	game->texture_east = mlx_load_png("src/render/assets/wolftextures2.png");
	if (!game->texture_east)
	{
		mlx_delete_texture(game->texture_north);
		mlx_delete_texture(game->texture_south);
		return (0);
	}

	// Chargement texture Ouest
	game->texture_west = mlx_load_png("src/render/assets/wolftextures2.png");
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

	int x = px / BLOCK_SIZE;
	int y = py / BLOCK_SIZE;
	if (game->map[y][x] == '1') {
		return (true);
	}
	return (false);
}

double fixed_dist(double x1, double y1, double x2, double y2, t_game *game) {

	double delta_x = x2 - x1;
	double delta_y = y2 - y1;
	double angle = atan2(delta_y, delta_x) - game->player.angle;
	double fix_dist = distance(delta_x, delta_y) * cos(angle);
	return (fix_dist);
}

void draw_line(t_game *game, double fx, int i)
{
	double ray_x = game->player.x;
	double ray_y = game->player.y;
	double cos_angle = cos(fx);
	double sin_angle = sin(fx);
	int side = 0;
	mlx_texture_t *texture;

	// Ajout d'une petite valeur epsilon pour éviter la division par zéro
	const double epsilon = 0.000001;
	if (fabs(cos_angle) < epsilon)
		cos_angle = epsilon;
	if (fabs(sin_angle) < epsilon)
		sin_angle = epsilon;

	while (!touch(ray_x, ray_y, game)) {
		ray_x += cos_angle;
		ray_y += sin_angle;
	}

	double wall_x;
	// Modification de la détection des côtés
	if (fabs(cos_angle) > fabs(sin_angle)) {
		side = 0;
		if (cos_angle > 0) {
			texture = game->texture_north;
			wall_x = ray_y / BLOCK_SIZE - floor(ray_y / BLOCK_SIZE);
		} else {
			texture = game->texture_south;
			wall_x = ray_y / BLOCK_SIZE - floor(ray_y / BLOCK_SIZE);
		}
	} else {
		side = 1;
		if (sin_angle > 0) {
			texture = game->texture_east;
			wall_x = ray_x / BLOCK_SIZE - floor(ray_x / BLOCK_SIZE);
		} else {
			texture = game->texture_west;
			wall_x = ray_x / BLOCK_SIZE - floor(ray_x / BLOCK_SIZE);
		}
	}

    double dist = fixed_dist(game->player.x, game->player.y, ray_x, ray_y, game);
    double height = (BLOCK_SIZE / dist) * (WINDOW_WIDTH / 2);
    int start_y = (WINDOW_HEIGHT - height) / 2;
    int end = start_y + height;

    if (start_y < 0) start_y = 0;
    if (end > WINDOW_HEIGHT) end = WINDOW_HEIGHT;

    int tex_x = (int)(wall_x * texture->width);
    if ((side == 0 && cos_angle > 0) || (side == 1 && sin_angle < 0))
        tex_x = texture->width - tex_x - 1;

    if (i >= 0 && i < WINDOW_WIDTH)
    {
        double step = (double)texture->height / height;
        double tex_pos = (start_y - (WINDOW_HEIGHT - height) / 2) * step;

        for (int y = start_y; y < end; y++)
        {
            int tex_y = (int)tex_pos & (texture->height - 1);
            uint8_t *pixel = &texture->pixels[(tex_y * texture->width + tex_x) * texture->bytes_per_pixel];

            double shade = 1.0 - (dist / (WINDOW_WIDTH / 2));
            if (shade < 0.0) shade = 0.0;

            uint8_t r = pixel[0] * 1;
            uint8_t g = pixel[1] * 1;
            uint8_t b = pixel[2] * 1;
            uint8_t a = pixel[3];

            mlx_put_pixel(game->image_global, i, y, get_rgba(r, g, b, a));
            tex_pos += step;
        }
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
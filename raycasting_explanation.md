# 🎮 Explication du Raycasting dans Cub3D

## 📚 Table des matières
1. [Introduction](#introduction)
2. [Structures de données](#structures)
3. [Initialisation](#initialisation)
4. [Boucle principale](#boucle-principale)
5. [Calculs de raycasting](#raycasting)
6. [Rendu des textures](#textures)
7. [Gestion des collisions](#collisions)

## 🎯 Introduction <a name="introduction"></a>
Le raycasting est une technique de rendu 3D qui simule une vue en perspective en lançant des rayons depuis la position du joueur. Cette technique a été rendue célèbre par Wolfenstein 3D.

## 🏗️ Structures de données <a name="structures"></a>
```c
typedef struct s_player
{
    double x;      // Position X du joueur
    double y;      // Position Y du joueur
    double angle;  // Angle de vue (en radians)
} t_player;

typedef struct s_game
{
    mlx_t *mlx;                // Instance MLX
    mlx_image_t *image_global; // Image de rendu
    t_player player;           // Données du joueur
    char **map;                // Carte du jeu
    mlx_texture_t *texture_north; // Textures des murs
    mlx_texture_t *texture_south;
    mlx_texture_t *texture_east;
    mlx_texture_t *texture_west;
} t_game;
```

## 🚀 Initialisation <a name="initialisation"></a>
1. **Position initiale du joueur** :
   ```c
   player->x = WINDOW_WIDTH / 2;
   player->y = WINDOW_HEIGHT / 2;
   player->angle = PI * 1.5;  // Regarde vers le haut
   ```

2. **Chargement des textures** :
   - Chaque mur a sa propre texture (Nord, Sud, Est, Ouest)
   - Format PNG supporté par MLX42
   - Gestion des erreurs avec libération propre de la mémoire

## 🔄 Boucle principale <a name="boucle-principale"></a>
Pour chaque frame :
1. Effacer l'écran
2. Dessiner le fond (ciel et sol)
3. Lancer les rayons pour chaque colonne de l'écran
4. Gérer les entrées utilisateur

## 📐 Calculs de raycasting <a name="raycasting"></a>

### 1. DDA (Digital Differential Analyzer) 🎯
```c
double delta_dist_x = fabs(1.0 / cos_angle);
double delta_dist_y = fabs(1.0 / sin_angle);
```
- Calcule la distance entre les intersections verticales et horizontales
- Évite la division par zéro avec une valeur très grande (1e30)

### 2. Calcul du pas 👣
```c
if (cos_angle < 0) {
    step_x = -1;
    side_dist_x = (ray_x - map_x * BLOCK_SIZE) * delta_dist_x;
} else {
    step_x = 1;
    side_dist_x = ((map_x + 1.0) * BLOCK_SIZE - ray_x) * delta_dist_x;
}
```
- Détermine la direction du rayon
- Calcule la distance initiale jusqu'à la prochaine intersection

### 3. Algorithme DDA 🔍
```c
while (!hit) {
    if (side_dist_x < side_dist_y) {
        side_dist_x += delta_dist_x * BLOCK_SIZE;
        map_x += step_x;
        side = 0;  // Mur vertical
    } else {
        side_dist_y += delta_dist_y * BLOCK_SIZE;
        map_y += step_y;
        side = 1;  // Mur horizontal
    }
}
```
- Avance le rayon jusqu'à toucher un mur
- Détermine quel type de mur est touché (vertical/horizontal)

## 🎨 Rendu des textures <a name="textures"></a>

### 1. Calcul des coordonnées de texture
```c
wall_x = ray_y + wall_dist * sin_angle;  // Pour murs verticaux
wall_x = wall_x - floor(wall_x / BLOCK_SIZE) * BLOCK_SIZE;
tex_x = (int)(wall_x * texture->width / BLOCK_SIZE);
```
- Détermine le point exact d'impact sur le mur
- Convertit en coordonnée de texture

### 2. Correction de la distorsion en poisson 🐟
```c
double perp_wall_dist = wall_dist * cos(fx - game->player.angle);
int line_height = (int)(WINDOW_HEIGHT / perp_wall_dist * BLOCK_SIZE);
```
- Corrige la distorsion due à la projection
- Calcule la hauteur apparente du mur

### 3. Application des textures et ombrage 🎨
```c
double shade = ft_clamp(1.0 - (perp_wall_dist / (WINDOW_WIDTH * 0.7)), 0.3, 1.0);
uint8_t r = (uint8_t)(pixel[0] * shade);
```
- Applique un effet d'ombrage basé sur la distance
- Limite l'assombrissement avec ft_clamp

## 🛡️ Gestion des collisions <a name="collisions"></a>
```c
bool is_wall(double px, double py, t_game *game)
{
    const double buffer = 10.0;  // Zone de collision
    // Vérifie plusieurs points autour du joueur
    for (double angle = 0; angle < 2 * PI; angle += PI / 4) {
        // ... vérifications de collision
    }
}
```
- Utilise une zone tampon autour du joueur
- Vérifie 8 points autour du joueur pour une collision précise
- Gère les limites de la carte et les murs

## 🎮 Contrôles
- W/↑ : Avancer
- S/↓ : Reculer
- A/← : Strafing gauche
- D/→ : Strafing droit
- Q : Rotation gauche
- E : Rotation droite
- ESC : Quitter

## 🔧 Optimisations
1. Utilisation de précalculs pour les angles
2. Gestion efficace de la mémoire avec les textures
3. Clipping des murs hors écran
4. Buffer de rendu optimisé avec MLX42
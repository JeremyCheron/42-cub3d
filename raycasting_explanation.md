Entrée dans le main :

Etape 1 : Check les arguments
- Si pas d'argument, affiche l'aide
- Si pas de map, affiche l'aide
- Si map invalide, affiche l'aide

Etape 2 : Initialise les données du jeu

- Initialise la fenêtre 
- Initialise l'image pricipale (image_global) pour la MLX
- Prends en compte la map (map de test pour le moment)
- Initialise le joueur (position, angle, etc)
- Initialise les textures (pour le moment, textures prédéfinies)

Etape 3 : Capture des événements
- Initialise les touches a capturer
- Gestion des mouvements du joueur

Etape 4 : Boucle principale
- Draw loop :
- - Efface l'écran
- - Dessine le fond (ciel et sol)
- - Lancer les rayons pour chaque colonne de l'écran

--- - - Pour chaque colonne, calcule la direction du rayon

cast_rays
Cast_rays :
fraction = PI / 3 = 60° Donc le FOV
/ divisé par WINDOW_WIDTH donc une fraction de 60° par pixel

Start_X : La gauche de la vision du joueurs, cette valeur va etre incrementer pour parcourir toute la vision du joueur avec fraction dans la bouvle
Donc on parcourt de i a WINDOW_WITH  donc de gaucghe a droite

Boucle d'affichage :



### Projet Programmation S3 - Dungeon Crawler 
## Prérequis
SDL2  
SDL2_image (bibliotèque non fournie dans SDL2 de base)

## Description
L'objectif du projet est de créer un **dungeon crawler 2D** avec une gestion de la caméra à la manière de Binding of Isaac(**Salle par salle**).  
Nous aimerions implémenter de la **génération procédurale** pour la création des salles ainsi que leurs contenus.  
Les salles contiendraient donc des ennemis, des obstacles et des objets que nous comptons gérer avec un **système de tiles**.  

## Comment le lancer
Il faut se placer dans le répertoire ../Base_SDL/ et entrer dans l'invité de commandes :
make  
./main

## Suivi
### Semaine 1 
-Création README.md 
### Semaine 2 
-Ajout d'une structure et de fonctions pour la gestion d'entités.  
-Ajout d'une structure et de fonctions pour la gestion des tiles répresentant le background.
### Semaine 3
-Vérification de la compatibilité du code avec Linux/Ubuntu de la FST  
-Création du makefile sous Linux  
-Réglage de problèmes dans l'installation de la bibliothéque ttf  
-Formation sur la gestion des collisions avec la sdl(Le code n'est pas encore fonctionnel)

### Semaine 4
-Ajout de la gestion du mouvement des entités  
-Ajout de la gestion du mouvement du joueur  
-Ajout de modularité dans l'organisation du projet  
-Le code sur la gestion des collisions nécessite encore du peaufinage  
-Formation sur la mise en place de la génération procédurale  

### Semaine 5  
-Ajout de la gestion des obstacles au sein d'une salle  
-Ajout de la collision du joueur avec les obstacles  
-Ajout de la création des ennemies à l'aide d'une pile de donnée  
-Ajout de l'affichage des ennemies  
-Changement des sprites pour des sprites libres de droit  
-Recherche sur les moyens de sauvegarde de salle du jeu à l'aide d'un fichier  
-Réécriture complète du Makefile pour la clareté et de la correction d'erreurs et ajout de SDL_image dedans

### Semaine 6  
-Ajout du mouvement des ennemies  
-Ajout du changement du sprite du joueur en fonction de la direction  
-Ajout de quatres types de mouvement différents pour les ennemies  
-Ajout de la génération procédurale des étages  

### Semaine 7  
-Ajout de la création des salles et des ennemies grâce à des fichier txt  
-Ajout de la mécanique de combat avec une épée associé au joueur  
-Ajout des collisions entre le joueur et les ennemies  
-Ajout de mur destructible avec l'épee  
-Nettoyage du code  


## Tableau d'organisation
https://trello.com/b/wG0z8xdt

### Auteurs
Jeannin Théo  
Borgondo David

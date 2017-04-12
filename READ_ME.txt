Mars_Attack

RAINOUARD Fabian 11406132
TARDY Martial 11407179
RULLIAT Clara 1406009

Compilation:
make

Exécution :
Pour la version texte : ./bin/progTXT
Pour la version SDL : ./bin/progSDL

Règles du jeu :
Il s'agit d'un jeu prenant pour modèle "Space Invaders"

But : Avoir le meilleur score en tuant les aliens.

Le vaisseau se déplace de droite à gauche. Il peut tirer des missiles sur des vagues d'aliens qui arrivent par le ciel.
A chaque alien tué, le joueur remporte des points, qui s'additionnent à son score.
Les aliens peuvent aussi tirer sur le vaisseau, lorsqu'ils le touchent, il perd une vie.
Il existe trois types d'aliens, selon leur nombre de vies. 
Le vaisseau possède 3 vies, lorsqu'il les a toutes épuisées il se détruit, la partie est finie et le cumul du score est stoppé.
Des protections sont présentes entre le vaisseau et les aliens pour protéger le vaisseau des missiles ennemis.
Le jeu fonctionne par niveaux. Plus le niveau augmente et plus les aliens ont un nombre de vies supérieur. Le gain de score augmente aussi :  lorsqu'un missile touche un alien, le score augmente de 100 fois le niveau en cours.
Jusqu'au niveau 3, les missiles aliens peuvent etre détruit par un missile vaisseau, après ce niveau ils ne peuvent plus etre atteints.

Les vies du vaisseau s'affichent en haut à gauche de la fenêtre, et les supermissiles disponibles en haut à droite.
Le score actuel, le meilleur score ainsi que le niveau actuel sont affichés en haut de la fenêtre.

Améliorations :
- Des cases "vie" s'affiche au fil des niveaux, elles permettent au vaisseau de récupérer une vie en tirant dessus.
- Des cases "étoile" permettent au vaisseau de récupérer un supermissile, qui tue tous les aliens d'une même colonne.


Commandes:
	Déplacements horizontaux : Flèches
	Tire : Barre Espace
	Tire supermissile : E
	Quitte le jeu : Q
	Pause : P
	Informations : I (utile seulement pour debugger)

Commandes de triche : utilisées pour debugger lors de la création du jeu
	Niveau superieur : Z
	Obtenir 10 supermissiles : R


Menu:
	Jouer ou Continuer Partie si une sauvegarde existe
	-------- ou Recommencer si une sauvegarde existe
	Commandes
	Volumes Musique
	Volumes Bruitage
	Initialiser Meilleur Score
	Quitter


Organisation archive:
bin 	- progSDL
	    - progTXT

data	-musiques	
            - AlexZavesa_-_Progressive_Trance_court.mp3
			- Dijelyo_-_dijelyo_-_my_drum_n_bass_court.mp3
			- SF-Alarmradar.mp3
			- SF-bullet-time_04sf.wav
			- sf_canon_01_court.wav

	- images	
	        - etoile.xcf
			- fond.JPG
			- missilealien.png
			- missilevaisseau1.png
			- missilevaisseau2.png
			- protection.png
			- soucoupe.xcf
			- soucoupe2.xcf
			- soucoupe3.xcf
			- vaisseau.xcf
			- vie.png
	- sauvegardeMS.txt
	- sauvegardeMap.txt
	- police.ttf

doc	- mars_attack.doxy
	- html		- index.html
	- latex
	- diporama.pdf
	- diagramme_modules.jpeg
	- Gantt.png

obj	- affichageSDL.o
	- alien.o
	- ensemblealien.o
	- ensemblemissile.o
	- ensembleprotection.o
	- jeu.o
	- jeuSDL.o
	- main.o
	- map.o
	- missile.o
	- position.o
	- protection.o
	- scores.o
	- vaisseau.o

src	- affichageSDL.h
	- alien.h
	- ensemblealien.h
	- ensemblemissile.h
	- ensembleprotection.h
	- jeu.h
	- jeuSDL.h
	- main.h
	- map.h
	- missile.h
	- position.h
	- protection.h
	- scores.h
	- vaisseau.h
	- affichageSDL.c
	- alien.c
	- ensemblealien.c
	- ensemblemissile.c
	- ensembleprotection.c
	- jeu.c
	- jeuSDL.c
	- main.c
	- map.c
	- missile.c
	- position.c
	- protection.
	- scores.c
	- vaisseau.c

Makefile
READ_ME.txt




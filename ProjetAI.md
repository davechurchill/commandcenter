# Équipe Symbolique: CommandCenter-Clone
Projet largement basé sur le projet CommandCenter écrit par [David Churchill](http://www.cs.mun.ca/~dchurchill/), qui est basé sur l'architecture de [UAlbertaBot](https://github.com/davechurchill/ualbertabot/wiki). Le bot est écrit en C++ et utilise l'API [StarCraft II AI API](https://github.com/Blizzard/s2client-api). Pour plus d'information du projet de base CommandCenter, lisez la [documentation officielle](README.md).

# Installation et compilation du projet (Windows)

* Télécharger et installer [Visual Studio 2017](https://www.visualstudio.com/downloads/)
* Télécharger et installer la [version précompiler de StarCraft II AI API](https://github.com/Blizzard/s2client-api#precompiled-libs).
* Télécharger et installer StarCraft II
  * Télécharger les "Map Packs" du jeu (Vous pouvez trouver les cartes [ici](https://github.com/Blizzard/s2client-proto#downloads))
  * Ajouter les cartes à la racine de `C:\Program Files (x86)\StarCraft II\Maps`. 
* Ajouter les variable système suivante: 
  * `SC2API_DIR`: chemin vers la SC2API (ex: `C:\Libraries\SC2API_Binary_vs2017`)
  * `SC2PATH`: chemin vers le jeu StarCraft II (ex: `C:\Program Files (x86)\StarCraft II`)
* Cloner le projer
* Ouvrir "CommandCenter/vs/CommandCenter.sln" dans VS2017
* Définir SC2API dans les librairies à inclure dans le projet Visual Studio.
  * Clic droit sur le projet CommandCenter dans VS2017
  * Sélectionner "Properties"
  * Sélectionner la configuration de compilation dans le coin gauche ("Release" ou "Debug")
  * Sélectionner "VC++ Directories" dans le menu à gauche
  * Modifier l'option "Include Directories" dans la table à droite pour `$(SC2API_DIR)\include;$(IncludePath)`
  * Modifier l'option "Library Directories" dans la table à droite pour `$(SC2API_DIR)\lib;$(LibraryPath)`
* Encore dans la fenêtre "Properties", sélectionner "Working Directory" dans le menu à gauche.
  * Modifier l'option "Debugging" pour `$(ProjectDir)/../bin/`
* Lancer l'exécution en appuyant sur la touche `F5`

# Changements apportés au projet de base CommandCenter

TODO

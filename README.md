# Projet C - P2 : Notre Rover MARC

**Lien du dépôt Git** : https://github.com/ismardn/proj-ti301-radouane-rasolorimanana-loutchmia.git

### Contributeurs : groupe A-6
- Ismaël RADOUANE
- Malalasoa RASOLOARIMANANA
- Laïli LOUTCHMIA

## Mode d'emploi
- Avant d'exécuter le programme, l'utilisateur choisi la carte qu'il souhaite utiliser (voir le dossier *maps*). Les paramètres initiaux sont la position et l'orientation de départ du robot ainsi que les limites de la carte et les types de sols. 
- Lors de l'exécution, le programme propose 7 types de mouvements possibles (TYPE_OF_MOVES_NUMBER) et en sélectionne 9 au hasard pour la phase (SELECTED_MOVES_NUMBER). Il en chosit ensuite 5 (EXECUTED_MOVES_NUMBER) parmi les 9 pour constituer la séquence à exécuter.
- Le robot avance selon le chemin des meilleurs mouvements, il peut arriver qu'il sorte de lacrte ou tombe sur une crevasse ce qui le fait perdre.
- S'il arrive à la station de base, alors c'est gagné.

### Fonctionnalités expérimentales - problèmes rencontrés
Il s'agit de fonctions facultatives avec quelques bugs donc ne sont pas implémentées : calcul du meilleur chemin sans construire tout l'arbre ainsi que l'implémentation de plusieurs phases.








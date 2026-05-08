# S2 | Prog&Algo: TD07 Graphes

## TD07 Graphes

**Chloé Chabaud**

# Exercice 1 (Prise en main)

Commandes tapées :

- `./td7.exe extract data/test.osm data/test_extract.graph` : extrait la carte dans le dossier data
- `./td7.exe simplify data/test_extract.graph` : simplification de la carte extraite
- `./td7.exe visualize data/test_extract.graph` : affichage de la carte simplifiée

# Exercice 2

## Question 1:

La structure WeightedGraph est définie dans WeightedGraph.hpp. Elle représente le graphe sous forme de liste d’adjacence : chaque nœud possède une liste d’arêtes contenant une destination et un poids.

PositionedGraph est définie dans le fichier PositionedGraph.hpp (dossier osm). Elle regroupe la structure du graphe (via WeightedGraph) ainsi que la position des nœuds (x, y).

## Question 2 :

'Extraction OSM' : permet de lire un fichier OpenStreetMap et de construire la structure du graphe.
'Simplification' : enlève les nœuds et arêtes inutiles ou non pertinentes.
'Visualisation' : permet d’afficher graphiquement le graphe

## Question 3: étapes de simplification

### Étape 1 : `keep_only_largest_connected_component`

On commence par détecter toutes les composantes connexes du graphe à l’aide d’un parcours en profondeur (DFS).

Pour chaque nœud non visité, on explore tous ses voisins accessibles et on les regroupe dans une même composante ( on a donc des ensembles de noeuds adjacents).  
On répète ce processus jusqu’à avoir exploré tout le graphe.

Ensuite, on conserve uniquement la plus grande composante connexe (le plus grand “îlot”) et on supprime toutes les autres.

#### Avantage

- Réduction importante du graphe en supprimant les parties isolées

#### Inconvénient

- Suppression de petites composantes potentiellement utiles

### Étape 2 : `remove_small_ending_edge`

On parcourt tous les nœuds du graphe.  
Si un nœud possède un seul voisin (degré 1) alors ce nœud est supprimé avec son arête.

#### Avantage

- Suppression des petites branches en fin de graphe inutiles

#### Inconvénient

- Certaines petites "routes" réelles peuvent être supprimées

### Étape 3 : `remove_degree_two_nodes_by_angle_threshold`

On parcourt tout le graphe
Pour chaques nœuds ayant exactement deux voisins,
on calcule l’angle formé par ses deux arêtes.

Si cet angle est proche de 180° (ligne droite), le nœud est supprimé et ses deux voisins sont directement connectés.

#### Avantage

- Simplifie en supprimant des neouds intermediaires, sans modifier la structure du graphe (lignes droites conservées)

#### Inconvénient

- Perte de précision au niveau de la direction/géométrie dans le graphe. On fait des approximations qui peuvent supprimer des données importantes

### Étape 4 : `group_nodes_by_connection_depth_and_proximity`

Pour chaque noeuds, on crée des groupes (clusters) de nœuds adjacents : ce sont des nœuds proches dans le graphe (peu d’arêtes entre eux).
Pour chaque voisin dans le cluster, on étudie leur distance spatiale (à partir de leurs positions).
On ne conserve que les nœuds suffisamment proches (distance < seuil de proximité).

Résultat : on obtient des groupes de nœuds, ce qui permet de fusionner certaines zones et de réduire le nombre de nœuds inutiles.

### Étape 5 : nouvelle simplification des nœuds de degré 2

Après les fusions, de nouveaux nœuds de degré 2 peuvent apparaître, on refait donc des approximation "de lignes droites" (étape 3)

EX 2

Question 1:
la structure WeightedGraph est définie dans WeightedGraph.hpp, et possède le numéro d'un noeud et la liste de ses aretes (struct avec desintaion et poids)

PositionedGraph est définie dans le fichier PositionedGraph.hpp issu du dossier osm
Il regroupe la structure du graphe ( donné par weightedGraph)
-une association entre chaque neoud et leur position (x,y) appelée nod

Question 2 :

extraction OSM: permet de lire le fichier OSM et d'en afficher la structure du graphe
simplification viens enlever les noeuds et les arrêtes inutiles/pas reliées
visualition permet d'afficher graphiquement le graphe

Question 3:
étapes de simplification

ETAPE 1: keep_only_largest_connected_component :
on cree une liste de noeud parcouru
une liste de noeud adjecent
utilise un parcourt en profondeur pr relever toutes les voisins du noeuds en question
on les ajoute dans une struct ( on a donc un ens de noeud adjacent)
on note le noeud comme visité
puis on refait sur des noeuds pas visité
on obtient donc des groupes d'adjacences
on retourne adjacences la plus grande ( le plus grand ilot)

avantages: on réduit la taille du graphe
incovénient: on perd quand même des réseaux qui peuvent être grand (juste 1 noeud en mois que le plus grand)

ETAPE 2 remove_small_ending_edge
on parcourt tous les noeuds, on regarde son nombre de voisin, si il est <= 1 on le supprime lui et toutes ses arrètes entrante ou sortantes
réduit encore le nbr de noeuds et dc sa taille

ETAPE 3 remove_degree_two_nodes_by_angle_threshold(graph, 30);
on parcourt tous les noeuds et on regarde tous ses voisins.
Si il en a exactement 2, on regarde l'angle formé par ses 2 arrêtes. Si environ = 180 degres, on le supprime et on relie ses voisins ( il était inutile car ligne droite).
Permet de supprimer des noeuds intermediraore inutile, ce qui ne ralonge pas la longueur entre le snoeuds pr autant
mais on fait des approcimation et peut être qu'on enlève des donnée importante
ETAPE 4: group_nodes_by_connection_depth_and_proximity
On parcourt chaque noeud, et pour chacun, on cree un cluster : un groupe avec ses voisins les assez proches ( en arrêtes) et lui mêmes. Pour chaque voisin dans le cluster, on regarde leur distance au niveau spacial ( en ftc den leur positioon)avec le neoud en question et on ne garde que ceux assez proche (distance< proximity)

résultat: on cree des groupes de noeuds, on enleve certain inutile

ETAPE 5
on refait des approximation de lignes droites (étape 3 le retour)

la commande :
./td7.exe extract data/test.osm data/test_extract.graph  
./td7.exe simplify data/test_extract.graph

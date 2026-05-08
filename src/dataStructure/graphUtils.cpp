#include "graphUtils.hpp"
#include "weightedGraph.hpp"

#include <vector>
#include <unordered_map>
#include <functional>
#include <queue>
#include <set>
#include <stack>
#include <algorithm>

using DataStructure::WeightedGraph;
using DataStructure::IDType;

void DFS(WeightedGraph const& graph, IDType const start, std::function<void(IDType const)> const& callback, std::function<bool(IDType const)> const& should_explore_neighbors) {
    std::set<IDType> visited {};
    std::stack<IDType> to_visit {};
    to_visit.push(start);
    while (!to_visit.empty()) {
        auto const current { to_visit.top() };
        to_visit.pop();

        if (visited.contains(current)) {
            continue;
        }

        visited.insert(current);
        callback(current);

        if (should_explore_neighbors(current)) {
            for (auto const& edge : graph.get_neighbors(current)) {
                to_visit.push(edge.to);
            }
        }
    }
}

void print_DFS(WeightedGraph const& graph, IDType const start) {
    /* TODO */
}


template<class T>
using min_priority_queue = std::priority_queue<T, std::vector<T>, std::greater<T>>;

// map of node id to pair of cost and parent node id (for path reconstruction)
std::unordered_map<IDType, std::pair<float, IDType>> Dijkstra(WeightedGraph const& graph, IDType const start, IDType const end) {
    // TABLEAU ASSOCIATIF DISTANCE NOEUD associe float(distance) avec idtype(parents)
    std::unordered_map<IDType, std::pair<float, IDType>> distances {};
    // priority queue of pair of current cost from starting node and current node id
    // this will sort node base on the cost (as pair are ordered with lexicographical order)
    //TAB DES NOEUDS A VISITER float (poids actuel), idtype(le noeud)
    //file de priorité
    min_priority_queue<std::pair<float, IDType>> to_visit {};

    to_visit.push({0.0f, start}); //on met le premier noeud dans les à visiter
    distances[start] = {0.0f, start}; //idem pr start

    /* TODO  Q1*/ 
    
    while (!to_visit.empty()) //tant que à visiter pas vide
        {
            //prend plus petite distance ie le haut de la file
            auto [cost, current_node]= to_visit.top();
             //on retire noeud courant de à visiter
            to_visit.pop();
            if (current_node == end){
                break;
            } //condition fin 
            else{
            
                    //ajout voisins, utilise get_neighboor
                for (auto const& voisin : graph.get_neighbors(current_node)) {
                    auto node_voisin = voisin.to;
                    float weight_voisin = voisin.weight;

                    //calcul distance du noeud en passant pas current
                    float new_cost = weight_voisin + cost;


                    

                    //on maj distance si necessaire: pas visté OU meilleur cout
                     if(!distances.contains(node_voisin) || distances[node_voisin].first>new_cost){ //poids enrigistré VS nouveau
                
                        //maj dans distance
                        distances[node_voisin]={new_cost,current_node};

                        //on remet le noeud dans à visister
                        to_visit.push({new_cost,node_voisin});
                        }
                      
            }
            }
        }
        
        return distances;
    }

std::vector<IDType> reconstruct_path(std::unordered_map<IDType, std::pair<float, IDType>> const& distances, IDType const start, IDType const end) {
    std::vector<IDType> path { };
    IDType current_node { end };
    while (current_node != start) {
        path.push_back(current_node);

        auto const find_current_node { distances.find(current_node) };
        if(find_current_node == distances.end()) {
            // if we reach a node that is not in the distances map, it means that there is no path from start to end
            return {};
        }
        else {
            // we update the current node to its parent node
            current_node = find_current_node->second.second;
        }
    }
    path.push_back(start);
    std::reverse(path.begin(), path.end());
    return path;
}

std::vector<IDType> dijkstra_path(WeightedGraph const& graph, IDType const start, IDType const end) {
    return reconstruct_path(Dijkstra(graph, start, end), start, end);
}
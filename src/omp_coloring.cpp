#include "omp_coloring.hpp"
#include <algorithm>
#include <iostream>
#include <ranges>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>

int OmpColoring::color_node(int node_id) {
    std::set<int> used_color;
    for (auto &adj_node : graph[node_id]) {
        if (nodes_color.contains(adj_node) && adj_node < node_id) {
            used_color.insert(nodes_color[adj_node]);
        }
    }
    int prev = -1;
    for (auto it = used_color.begin(); it != used_color.end() && *it <= prev + 1; ++it) {
        prev = *it;
    }
    return prev + 1;
}

void OmpColoring::color_graph(){
    
    //Initialize the nodes_color 
    for (auto node_id : nodes) {
        nodes_color[node_id] = -1;
    }

    // Parallelize the coloring process
    #pragma omp parallel
    {
        #pragma omp for
        for (auto node_id : nodes) {
            int color = color_node(node_id);
            nodes_color[node_id] = color;
        }
    }

    // Fix conflict if adjacent has same color by assigning it with a new value


}
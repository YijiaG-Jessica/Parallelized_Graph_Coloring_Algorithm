#include "omp_coloring.hpp"
#include <algorithm>
#include <iostream>
#include <ranges>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>

void OmpColoring::build_graph() {
    for (auto [node1, node2] : edges) {
        graph[node1].push_back(node2);
        graph[node2].push_back(node1);
    }
}


int OmpColoring::color_node(int node_id) {
    std::set<int> used_color;
    for (auto &adj_node : graph[node_id]) {
        if (nodes_color.count(adj_node) == 1 && adj_node < node_id) {
            used_color.insert(nodes_color[adj_node]);
        }
    }
    int prev = -1;
    for (auto it = used_color.begin(); it != used_color.end() && *it <= prev + 1; ++it) {
        prev = *it;
    }
    return prev + 1;
}

void OmpColoring::color_graph() {
    std::set<int> used_color;

    //Initialize the nodes_color
    for (auto node_id : nodes) {
        nodes_color[node_id] = -1;
    }

    // Parallelize the coloring process
    #pragma omp parallel
    {
        #pragma omp for shared(used_color)
        for (auto node_id : nodes) {
            int color = color_node(node_id);
            nodes_color[node_id] = color;
            used_color.insert(color);
        }
    }

    // Fix conflict if adjacent has same color by assigning it with a new value
    #pragma omp parallel for shared(graph, node_colors, used_color)
    for (auto node_id : nodes) {
        int cur_color = nodes_color[node_id];
        for (auto &adj_node : graph[node_id]) {
            if (cur_color == nodes_color[adj_node]) {
                // If cur node color has the same color with one of it's adjcent node, update current node color to a new color
                #pragma omp atomic capture
                int updated_color= [&]() {
                    int prev = -1;
                    for (auto it = used_color.begin(); it != used_color.end() && *it <= prev + 1; ++it) {
                        prev = *it;
                    }
                    return prev + 1;
                }();
                nodes_color[node_id] = updated_color;
                used_color.insert(updated_color);
                break;
            }
        }
    }

    //Optimization
    #pragma omp parallel for shared(graph, colors)
    for (auto node_id : nodes){
        int maxNeighbor = 0;
        int maxColor = 0;
        for (auto neighbor : graph[node_id]){
            maxNeighbor = std::max(maxNeighbor, neighbor);
            maxColor = std::max(maxColor, nodes_color[neighbor]);
        }
        if (maxColor < nodes_color[node_id] && maxNeighbor < node_id){
            nodes_color[node_id] = maxColor + 1;
        }
    }

}


void OmpColoring::print_node_color() {
    for (auto [key, val] : nodes_color) {
        std::cout << "Node: " << key << " Color: " << val << std::endl;
    }
}

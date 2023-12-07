/*The Largest-Degree-First (LDF) algorithm for graph coloring*/

#include "ldf_coloring.hpp"
#include <algorithm>
#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include <omp.h>

// Constructor
// LdfColoring::LdfColoring(std::vector<std::pair<int, int>> edges) : edges(edges) {}


// Calculate degrees of nodes
void LdfColoring::calculate_degrees() {
    #pragma omp parallel for
    for (auto& [node, neighbors] : graph) {
        degrees[node] = neighbors.size();
    }
}

// Sort nodes by degree
std::vector<int> LdfColoring::sort_nodes_by_degree() {
    std::vector<int> nodes;
    for (auto& [node, _] : degrees) {
        nodes.push_back(node);
    }
    std::sort(nodes.begin(), nodes.end(), [&](int a, int b) {
        return degrees[a] > degrees[b];
    });
    return nodes;
}

// Color graph using Largest-Degree-First algorithm
void LdfColoring::color_graph() {
    calculate_degrees();
    std::vector<int> nodes = sort_nodes_by_degree();

    #pragma omp parallel for
    for (int i = 0; i < nodes.size(); i++) {
        int node = nodes[i];
        std::set<int> used_colors;
        for (int neighbor : graph[node]) {
            if (nodes_color.find(neighbor) != nodes_color.end()) {
                used_colors.insert(nodes_color[neighbor]);
            }
        }
        int color = 1;
        while (used_colors.find(color) != used_colors.end()) {
            color++;
        }

        #pragma omp critical
        nodes_color[node] = color;
    }
}


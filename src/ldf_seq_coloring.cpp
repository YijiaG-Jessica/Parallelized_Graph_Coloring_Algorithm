
#include "ldf_seq_coloring.hpp"
#include <algorithm>
#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include <omp.h>

// Constructor
SeqLdfColoring::SeqLdfColoring(std::vector<std::pair<int, int>> edges) : edges(edges) {}

// Build graph from edges
void SeqLdfColoring::build_graph() {
    for (auto [node1, node2] : edges) {
        graph[node1].push_back(node2);
        graph[node2].push_back(node1);
    }
}

// Calculate degrees of nodes
void SeqLdfColoring::calculate_degrees() {
    for (auto& [node, neighbors] : graph) {
        degrees[node] = neighbors.size();
    }
}

// Sort nodes by degree
std::vector<int> SeqLdfColoring::sort_nodes_by_degree() {
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
void SeqLdfColoring::color_graph() {
    std::vector<int> nodes = sort_nodes_by_degree();
    for (int node : nodes) {
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
        nodes_color[node] = color;
    }
}
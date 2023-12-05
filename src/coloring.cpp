#include "coloring.hpp"
#include <algorithm>
#include <iostream>
#include <ranges>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>

void Coloring::build_graph() {
    for (auto [node1, node2] : edges) {
        graph[node1].push_back(node2);
        graph[node2].push_back(node1);
    }
}

void Coloring::print_node_color() {
    for (auto [key, val] : nodes_color) {
        std::cout << "Node: " << key << " Color: " << val << std::endl;
    }
}
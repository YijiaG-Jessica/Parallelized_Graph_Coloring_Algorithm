#include "seq_coloring.hpp"
#include <algorithm>
#include <iostream>
#include <ranges>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>

void SeqColoring::build_graph() {
    for (auto [node1, node2] : edges) {
        graph[node1].push_back(node2);
        graph[node2].push_back(node1);
    }
    
}

int SeqColoring::color_node(int node_id) {
    std::set<int> used_color;
    for (auto &adj_node : graph[node_id]) {
        if (nodes_color.count(adj_node) == 1) {
            used_color.insert(nodes_color[adj_node]);
        }
    }

    // int prev = -1;
    // for (auto it = used_color.begin(); it != used_color.end() && *it <= prev + 1; ++it) {
    //     prev = *it;
    // }

    // return prev + 1;
    int lowest = [&]() {
        int prev = -1;
        for (auto it = used_color.begin(); it != used_color.end() && *it <= prev + 1; ++it) {
            prev = *it;
        }
        return prev + 1;
    }();
    return lowest;
}


void SeqColoring::color_graph() {
    for (auto i : nodes) {
        nodes_color[i] = color_node(i);
    }
}


void SeqColoring::print_node_color() {
    for (auto [key, val] : nodes_color) {
        std::cout << "Node: " << key << " Color: " << val << std::endl;
    }
}

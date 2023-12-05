#include "seq_coloring.hpp"
#include <algorithm>
#include <iostream>
#include <ranges>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>

int SeqColoring::color_node(int node_id) {
    std::set<int> used_color;
    for (auto &adj_node : graph[node_id]) {
        if (nodes_color.contains(adj_node)) {
            used_color.insert(nodes_color[adj_node]);
        }
    }

    int prev = -1;
    for (auto it = used_color.begin(); it != used_color.end() && *it <= prev + 1; ++it) {
        prev = *it;
    }

    return prev + 1;
}


void SeqColoring::color_graph() {
    for (auto i : nodes) {
        nodes_color[i] = color_node(i);
    }
}


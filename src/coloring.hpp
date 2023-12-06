#pragma once

#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class Coloring {
public:
    std::unordered_map<int, std::vector<int>> graph;
    std::unordered_map<int, int> nodes_color;

    Coloring(std::vector<int> const &_nodes, std::vector<std::pair<int, int>> const &_edges)
        : nodes(_nodes),
          edges(_edges) {}

    /*Create the graph with given nodes, pairs, graph*/
    void build_graph();

    virtual void color_graph() = 0;

    /*Print a pair with its color*/
    void print_node_color();

protected:
    std::vector<int> nodes;
    std::vector<std::pair<int, int>> edges;
};
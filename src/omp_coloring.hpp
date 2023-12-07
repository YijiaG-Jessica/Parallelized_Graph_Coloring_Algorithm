#pragma once

#include "coloring.hpp"

class OmpColoring {
private:
    std::vector<int> nodes;
    std::vector<std::pair<int, int>> edges;
    /* 
     * Color one node with "first available color" method with respoect to its adjacent nodes' color type
     */
    int color_node(int node);

public:
    std::unordered_map<int, std::vector<int>> graph;
    std::unordered_map<int, int> nodes_color;

    OmpColoring(std::vector<int> const &_nodes, std::vector<std::pair<int, int>> const &_edges)
        : nodes(_nodes),
          edges(_edges) {}

    /*Create the graph with given nodes, pairs, graph*/ 
    void build_graph();

    /*
     * Call color_node in parallel
     * This might cause some color conflicts due to that the nodes are not colored in seq
     * Atomically update the conflict node color with a new color for cur-node
     */
    void color_graph();

    /*Print a pair with its color*/
    void print_node_color();
};
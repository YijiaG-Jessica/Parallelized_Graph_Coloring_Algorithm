#pragma once
#include <algorithm>
#include <iostream>
#include <ranges>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>
// #include "coloring.hpp"



/*Fast but not optimal*/
class SeqColoring {
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

    SeqColoring(std::vector<int> const &_nodes, std::vector<std::pair<int, int>> const &_edges)
        : nodes(_nodes),
          edges(_edges) {
          }

    /*Create the graph with given nodes, pairs, graph*/
    void build_graph();

    /*Traverse throughall the node according to node id and color each node using color_node()*/
    void color_graph();

    void print_node_color();
};
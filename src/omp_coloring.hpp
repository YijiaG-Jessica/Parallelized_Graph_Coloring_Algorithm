#pragma once

#include "coloring.hpp"

class OmpColoring : public Coloring {
private:
    /* 
     * Color one node with "first available color" method with respoect to its adjacent nodes' color type
     */
    int color_node(int node);

public:
    /*Create the graph with given nodes, pairs, graph*/ 
    virtual void build_graph() final;

    /*
     * Call color_node in parallel
     * This might cause some color conflicts due to that the nodes are not colored in seq
     * Atomically update the conflict node color with a new color for cur-node
     */
    virtual void color_graph() final;

    /*Print a pair with its color*/
    virtual void print_node_color() final;
};
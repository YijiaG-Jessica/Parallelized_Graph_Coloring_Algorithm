#pragma once

#include "coloring.hpp"


/*Fast but not optimal*/
class SeqColoring : public Coloring {
private:
    /* 
     * Color one node with "first available color" method with respoect to its adjacent nodes' color type
     */
    int color_node(int node);

public:
    /*Create the graph with given nodes, pairs, graph*/
    virtual void build_graph() final;

    /*Traverse throughall the node according to node id and color each node using color_node()*/
    virtual void color_graph() final;
};
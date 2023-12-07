#pragma once

#include "coloring.hpp"


/*Fast but not optimal*/
class LdfColoring : public Coloring {
private:
    std::unordered_map<int, int> degrees;
    void calculate_degrees();
    std::vector<int> sort_nodes_by_degree();
    int color_node(int node);

public:
    //LdfColoring(std::vector<std::pair<int, int>> edges);
    /*Create the graph with given nodes, pairs, graph*/
    virtual void build_graph() final;

    /*Traverse throughall the node according to node id and color each node using color_node()*/
    virtual void color_graph() final;
};
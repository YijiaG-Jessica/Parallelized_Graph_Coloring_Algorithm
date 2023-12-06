#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <strings>
#include <string>

#include <coloring.hpp>
#include <seq_coloring.hpp>
#include <omp_coloring.hpp>
#include <ldf_coloring.hpp>

void read_testcase(std::string filename, std::vector<int> &nodes, std::vector<std::pair<int, int>> edges){
    std::ifstream fs;
    fs.open(filename);

    std::string line;
    std::getline(fs, line);
    std::istringstream iss(line);
    std::string str;
    std::getline(iss, str, '\n');
    int num_node = (int) atoi(str.c_str());

    for (int i = 0; i < num_node; i++) {
        nodes.push_back(i);
    }

    while(std::getline(fs, line)) {
        std::istringstream iss2(line);
        std::getline(iss2, str, ' ');
        int v1 = (int) atoi(str.c_str());
        std::getline(iss2, str, '\n');
        int v2 = (int) atoi(str.c_str());
        edges.push_back(std::make_pair(v1, v2));
    }
}


int main(int argc, char* argv[]){
    /*arg1: filename, arg2: method{seq, omp, ldf}*/
    if (argc != 3) {
        std::cout << "Arguments Not Valid: ./color <filename> <method>" << std::endl;
    }
    std::string filename = argv[1];
    std::string method = argv[2];

    std::vector<int> nodes;
    std::vector<std::pair<int, int>> edges;

    //Read from testcases
    read_testcase(filename, nodes, edges);

    if (method == "seq"){
        SeqColoring color_seq_graph(nodes, edges);
        color_seq_graph.color_graph();
        color_seq_graph.print_node_color();

    } else if (method == "omp"){
        OmpColoring color_omp_graph(nodes, edges);
        color_omp_graph.color_graph();
        color_omp_graph.print_node_color();

    } else if (method == "ldf"){
        LdfColoring color_ldf_graph(ndoes, edges);
        color_ldf_graph.color_graph();
        color_ldf_graph.print_node_color();
    }


}
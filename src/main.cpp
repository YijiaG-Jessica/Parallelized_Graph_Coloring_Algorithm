#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "seq_coloring.hpp"
#include "omp_coloring.hpp"
#include "timer.h"

void read_testcase(std::string filename, std::vector<int> &nodes, std::vector<std::pair<int, int>> &edges){
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

void print_info(double time_spent, std::unordered_map<int, int> colors){
    std::cout.setf(std::ios::fixed, std::ios::floatfield);
    std::cout.precision(5);
    std::cout << "Time spent: " << time_spent << std::endl;
    std::cout << "Colored with ";
    int max = 0;
    for (auto &color : colors) {
        max = std::max(max, color.second);
    }
    std::cout << max + 1 << " colors\n"; 
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

    Timer t;
    std::unordered_map<int, int> colors;
    if (method == "seq-greedy"){
        std::cout << "Start Sequential Graph Coloring with Greedy Algorithm" << std::endl;
        t.reset();
        SeqColoring color_seq_graph(nodes, edges);
        color_seq_graph.build_graph();
        color_seq_graph.color_graph();
        //color_seq_graph.print_node_color();
        double time_spent = t.elapsed();
        print_info(time_spent, color_seq_graph.nodes_color);
    } 
    else if (method == "omp-gready"){
        std::cout << "Start Parallelized Graph Coloring with Gready Algorithm" << std::endl;
        OmpColoring color_omp_graph(nodes, edges);
        t.reset();
        color_omp_graph.build_graph();
        color_omp_graph.color_graph();
        color_omp_graph.print_node_color();
        double time_spent = t.elapsed();
        print_info(time_spent, color_omp_graph.nodes_color);
    } else if (method == "seq-ldf"){
        std::cout << "Start Sequential Graph Coloring with Largest Degree First" << std::endl;


    } else if (method == "omp-ldf"){
        std::cout << "Start Parallelized Graph Coloring with Largest Degree First" << std::endl;
    }

    


    return 0;

}
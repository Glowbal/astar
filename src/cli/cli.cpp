#include <stdio.h>
#include <string>
#include <regex>
#include <iostream>
#include <fstream>
#include <sstream>

#include <astar\AStar.h>

namespace han {
    namespace ap {
        namespace cli {
            enum arg_options {
                output_file,
                pretty_output
            };

            uint32_t find_arg_code(std::string arg_) {
                if (arg_ == "-o") return arg_options::output_file;
                if (arg_ == "-p") return arg_options::pretty_output;

                return -1;
            }
        }
    }
}


int main(int argc, char **argv) {
    uint32_t arg_index = 1;
    if (argc < 2) {
        std::cout << "Usage: cli.exe [-p] [-o output.sqf] input.sqf\n";
    //    return 0;
    }

    HAN::NodePtrs nodes;
    for (int i = 0; i <= 30; ++i) {
        for (int j = 0; j <= 17; ++j) {
            HAN::NodePtr node = std::shared_ptr<HAN::Node>(new HAN::Node(i, j));
            if (j == 12 && i > 3 && i < 15)
                node->accessable = false;

            if (j == 5 && i > 2 && i < 15)
                node->accessable = false;

            if (i == 15 && j < 15)
                node->accessable = false;
            
            if (i == 20 && j > 10)
                node->accessable = false;
            nodes.push_back(node);
        }
    }
    HAN::Grid grid = HAN::Grid("My Grid name", nodes);

    HAN::AStar aStar = HAN::AStar(grid);

    HAN::NodePtr start = HAN::NodePtr(new HAN::Node(0, 0));
    HAN::NodePtr goal = HAN::NodePtr(new HAN::Node(27, 16));

    auto path = aStar.Calculate(start, goal);

    grid.print(path);

    grid.print(aStar.Calculate(HAN::NodePtr(new HAN::Node(0, 0)), HAN::NodePtr(new HAN::Node(25, 2))));
    grid.print(aStar.Calculate(HAN::NodePtr(new HAN::Node(10, 10)), HAN::NodePtr(new HAN::Node(0, 0))));
    grid.print(aStar.Calculate(HAN::NodePtr(new HAN::Node(14, 4)), HAN::NodePtr(new HAN::Node(0, 0))));
    
    aStar.SetHeuristic(7); 
    grid.print(aStar.Calculate(HAN::NodePtr(new HAN::Node(14, 4)), HAN::NodePtr(new HAN::Node(0, 0))));

    return 0;
}

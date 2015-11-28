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
    std::string input_filename = "grid.txt"; // (argv[argc - 1]);
    std::string output_filename = "output_example.txt";
    /*bool do_pretty = false;
    for (arg_index; arg_index < argc - 1; ++arg_index) {
        std::string arg(argv[arg_index]);
        switch (han::ap::cli::find_arg_code(arg)) {
        case han::ap::cli::arg_options::output_file:
            output_filename = std::string(argv[++arg_index]);
            break;
        case han::ap::cli::arg_options::pretty_output:
            do_pretty = true;
            break;
        };
    }

    std::ifstream input_file(input_filename);
    if (!input_file.is_open()) {
        std::cout << "Error: Cannot find input file \"" << input_filename << "\n";
        return 1;
    }
    std::string input_str((std::istreambuf_iterator<char>(input_file)), std::istreambuf_iterator<char>());
    */
    HAN::Grid grid = HAN::Grid(input_filename);

    HAN::AStar aStar = HAN::AStar(grid);

    auto path = aStar.Calculate(std::shared_ptr<HAN::Node>(new HAN::Node(0,0)), std::shared_ptr<HAN::Node>(new HAN::Node(0, 6)));

    grid.print(path);

    std::string output = "";
    std::ofstream compile_file(output_filename);
    if (!compile_file.is_open()) {
        std::cout << "Error: Cannot open output file \"" << input_filename << "\n";
        return 1;
    }
    compile_file << output;

    return 0;
}

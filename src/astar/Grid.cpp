/*
 * Grid.cpp
 *
 *  Created on: 10 dec. 2014
 *      Author: Thomas
 */

#include "Grid.h"
#include <fstream>
#include <sstream>
#include <iostream>

namespace HAN
{
    Grid::Grid(const std::string& fileName) :
        name(fileName)
    {
        load(fileName);
    }

    Grid::Grid(const Grid& wh) :
        nodes(wh.nodes), name(wh.name)
    {

    }

    Grid::Grid(const std::string& aName, const NodePtrs& someNodes) :
        name(aName), nodes(someNodes)
    {
    }

    Grid::~Grid()
    {

    }

    void Grid::load(const std::string& fileName)
    {
        nodes.clear();

        std::ifstream file(fileName);
        std::string line;
        while (std::getline(file, line))
        {
            try
            {
                if (line == "")
                    break;

                std::stringstream stream;
                stream << line;

                unsigned short x;
                unsigned short y;

                stream >> x >> y;

                for (int i = 0; i < x; ++i) {
                    for (int j = 0; j < j; ++j) {
                        NodePtr node = std::shared_ptr<Node>(new Node(i, j));
                        nodes.push_back(node);
                    }
                }
            }
            catch (std::exception& e)
            {
                std::cout << "Caught an exception: " << e.what() << std::endl;
            }
            catch (...)
            {
                std::cout << "Caught an unknown exception" << std::endl;
            }
        }
    }

    NodePtrs Grid::GetNodes()
    {
        return nodes;
    }

    bool Grid::isValidNode(NodePtr aNode) {
        return true;
    }

    NodePtrs Grid::findNeighbours(NodePtr aNode) {
        NodePtrs neighbours = NodePtrs();
        
        // This can be precalculated
        for (auto node : nodes) {
            if (!node->accessable)
                continue;
            // horizontal
            if (node->x == aNode->x && std::abs(node->y - aNode->y) == 1) {
                neighbours.push_back(node);
            }
            // vertical
            if (node->y == aNode->y && std::abs(node->x - aNode->x) == 1) {
                neighbours.push_back(node);
            }
            // diagonal
            if (std::abs(node->y - aNode->y) == 1 && std::abs(node->x - aNode->x) == 1) {
                neighbours.push_back(node);
            }
        }
        return neighbours;
    }

    void Grid::print(NodePtrs aPath) {
        int currentLine = 0;
        int nodeN = 0;

        for (auto node : nodes) {
            if (node->x != currentLine) {
                currentLine++;
                std::cout << std::endl; // end of line here
                std::cout << std::endl; // double end of line for extra spacing
            }
            bool inPath = false;
            for (auto pathNode : aPath) {
                if (pathNode == node)
                {
                    inPath = true;
                    break;
                }
            }
            if (node->accessable) {
                std::cout << "[";
                //std::cout << "[" << nodeN << "|h" << node->heuristicValue << ",c" << node->cost;
                if (inPath) {
                    std::cout << " X ";
                }
                else {
                    if (node->fValue > 0) {
                        if (node->fValue < 100) {
                            std::cout << 0;
                        }
                        if (node->fValue < 10) {
                            std::cout << 0;
                        }
                        std::cout << node->fValue;
                    }
                    else {
                        std::cout << "   ";
                    }
                }
                std::cout << "] ";
            }
            else {
                std::cout << "----- ";
            }
            nodeN++;
        }
    }

    void Grid::resetGrid() {
        for (auto node : nodes) {
            node->cost = 0;
            node->heuristicValue = 0;
            node->fValue = 0;
            node->parentNode = nullptr;
        }
    }
    void Grid::operator=(const Grid& rhs)
    {
        if (&rhs != this)
        {
            nodes = rhs.nodes;
            name = rhs.name;
        }
    }

    void Grid::operator=(const std::shared_ptr<Grid> rhs)
    {
        if ((Grid*)&rhs != this)
        {
            nodes = rhs->nodes;
            name = rhs->name;
        }
    }
} /* namespace HAN */

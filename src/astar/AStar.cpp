/*
 * AStar.cpp
 *
 *  Created on: 10 dec. 2014
 *      Author: Thomas
 */

#include "AStar.h"
#include <memory>
#include <iostream>
#include <exception>

namespace HAN
{

    AStar::AStar(const HAN::Grid& aGrid) :
        Grid(aGrid)
    {

    }

    AStar::~AStar()
    {

    }

    NodePtrs AStar::Calculate(NodePtr start, NodePtr goal)
    {
        
        if (!Grid.isValidNode(start) || !Grid.isValidNode(goal))
        {
            // EXECPTION. Nodes do not exist within this Grid.
            throw std::invalid_argument("Starting Node or goal are not valid within the Grid");
        }
        std::cout << "Starting path calculations " << std::endl;

        // clear our lists
        openList.clear();
        closedList.clear();
        
        // reset all our nodes values


        CalculateStep(start, goal);

        // trace back parents from goal to nullptr. Must have reached goal at the last element
        NodePtrs shortestPath = NodePtrs();

        NodePtr currStep = goal;
        while (currStep != nullptr) {
            std::cout << "NODE STEP: " << currStep->asString() << std::endl;
            shortestPath.push_back(currStep);
            currStep = currStep->parentNode;
        }

        // TODO reverse the list and we have our path

        return shortestPath;
    }

    void AStar::CalculateStep(NodePtr aNode, NodePtr goal) {
        auto neighbours = findNeighbours(aNode);

        for (auto node : neighbours) {            
            if (*node == *goal) {
                goal->parentNode = aNode;

                return; // First to reach our goal is here
            }

            // If in closed list, skip this. We already evaluated the node
            if (!InClosedList(node)) {
     
                if (node->parentNode == nullptr) { // Means this is the first time we are evaluating this node
                    AddtoOpenList(node); // this is an open node

                    // TODO if we can access this node
                    node->heuristicValue = GetHeuristic(node, goal); // Movement from our neighbour to our goal
                    node->cost = GetMovementCost(aNode, node); // Movement cost from our current node to our neighbouring node
                    node->parentNode = aNode;
                }
                else {
                    // Calculate if we want to leave this node alone.
                    // This is the case if our own movement costs + movement costs towards neighbour node
                    // are lower as the movement costs of the neighbour node already calculated.
                    //
                    // If that is the case, we want to re-parent the node to our node
                    // and reset the movement costs on it
                    auto newCosts = GetMovementCost(node, goal);
                    if (newCosts >= node->cost) {
                        continue; // It isn't shorter or cheaper from this node
                    }
                    node->cost = newCosts;
                    node->parentNode = aNode;
                }

                node->fValue = node->heuristicValue + node->cost;
            }
        }
        if (openList.size() == 0) {
            return; // impossible to solve
           // throw new std::exception("Empty open list");
        }

        NodePtr smallestNode = *openList.begin();
        for (auto openNode : openList) {
            if (openNode->fValue < smallestNode->fValue) {
                smallestNode = openNode;
            }
        }
        if (smallestNode == nullptr) {
            throw new std::exception("Couldn't find anything in the open list! Have we evaluated all our options?");
        }

        // add our current node to our closed list -> we already evaluated this
        AddtoClosedList(aNode);
        RemoveFromOpenList(aNode); // Remove our node from the open list and add to closed list
        CalculateStep(smallestNode, goal); // recursively calculate our path
    }

    NodePtrs AStar::findNeighbours(NodePtr aNode)
    {
        return Grid.findNeighbours(aNode);
    }

    unsigned short AStar::GetHeuristic(NodePtr from, NodePtr target) { 
        return from->distanceTo(*target);
    } // distance from to distance

    unsigned short AStar::GetMovementCost(NodePtr from, NodePtr to) {
        // Cost table:
        // horizontal or vertical = 10
        // Diagional = 14
        // formula: costs to move to + from.cost;

        if (from->x == to->x || from->y == to->y) {
            return 10 + from->cost;
        }
        else { // assume diagional
            return 14 + from->cost;
        }
    }

    bool AStar::InOpenList(NodePtr aNode) {
        for (auto node : openList) {
            if (*node == *aNode)
                return true;
        }
        return false;
    }

    bool AStar::InClosedList(NodePtr aNode) {
        for (auto node : closedList) {
            if (*node == *aNode)
                return true;
        }
        return false;
    }

    void AStar::AddtoOpenList(NodePtr aNode) {
        openList.push_back(aNode);
    }
    void AStar::AddtoClosedList(NodePtr aNode) {
        closedList.push_back(aNode);
    }

    void AStar::RemoveFromOpenList(NodePtr aNode) {
        if (openList.size() == 0)
            return; // nothing to remove

        for (auto it = openList.begin(); it != openList.end(); ++it) {
            if (*it == aNode) {
                openList.erase(it);
                return;
            }
        }
    }
} /* namespace HAN */

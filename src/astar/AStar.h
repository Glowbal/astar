/*
 * AStar.h
 *
 *  Created on: 10 dec. 2014
 *      Author: Thomas
 */

#ifndef ASTAR_H_
#define ASTAR_H_

#include "Grid.h"
#include <vector>

namespace HAN
{
    typedef std::vector<Node> Path;

    class AStar
    {
    public:
        AStar(const HAN::Grid& aGrid);
        virtual ~AStar();

        /**
         * Calculate the shortest path from start to goal
         *
         * @param start The starting Node
         * @param goal The goal of the to be calculated path
         * @param fewestInteresections Optional. Check for fewest intersections instead of shortest route.
         *
         * @return Shared NodePtrs to the shortest path
         */
        NodePtrs Calculate(NodePtr start, NodePtr goal);
        void SetHeuristic(float multiply_);

    private:

        void CalculateStep(NodePtr aNode, NodePtr goal, int stepC);

        /**
         * Find the neighbors of a Node
         * @param aNode The Node for which we will try to find neighbors.
         *
         * @return Vector with connecting Nodes.
         */
        NodePtrs findNeighbours(NodePtr aNode);

        float GetHeuristic(NodePtr from, NodePtr target); // distance from to distance

        float GetMovementCost(NodePtr from, NodePtr to);

        bool InOpenList(NodePtr aNode);
        bool InClosedList(NodePtr aNode);

        void AddtoOpenList(NodePtr aNode);
        void AddtoClosedList(NodePtr aNode);

        void RemoveFromOpenList(NodePtr aNode);

        Grid Grid;

        std::vector<NodePtr> openList;
        std::vector<NodePtr> closedList;
        float multiplyH;

    };

} /* namespace HAN */

#endif /* ASTAR_H_ */

/*
 * AStar.h
 *
 *  Created on: 10 dec. 2014
 *      Author: Thomas
 */

#ifndef ASTAR_H_
#define ASTAR_H_

#include "Warehouse/Warehouse.h"
#include "Path.h"
#include <vector>

namespace Car
{

    class AStar
    {
    public:
        AStar(const Car::Warehouse& aWarehouse);
        virtual ~AStar();

        /**
         * Calculate the shortest path from start to goal
         *
         * @param start The starting point
         * @param goal The goal of the to be calculated path
         * @param fewestInteresections Optional. Check for fewest intersections instead of shortest route.
         *
         * @return Shared Pointer to the shortest path
         */
        Path Calculate(const Car::Point& start, const Car::Point& goal, bool fewestIntersections = false);

    private:

        /**
         * Find the neighbors of a point
         * @param aPoint The point for which we will try to find neighbors.
         *
         * @return Vector with connecting points.
         */
        std::vector<Point> findNeighbours(const Car::Point& aPoint);

        Warehouse warehouse;
    };

} /* namespace Car */

#endif /* ASTAR_H_ */

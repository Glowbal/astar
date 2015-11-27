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
#include "Logger.hpp"

namespace Car
{

    AStar::AStar(const Car::Warehouse& aWarehouse) :
        warehouse(aWarehouse)
    {

    }

    AStar::~AStar()
    {

    }

    Path AStar::Calculate(const Car::Point& start, const Car::Point& goal, bool fewestIntersections /*  = false */)
    {
        std::stringstream stream;
        stream << start.asString() << " " << goal.asString() << std::endl;
        Logger::log(stream.str());
        if (!warehouse.isValidPoint(start) || !warehouse.isValidPoint(goal))
        {
            // EXECPTION. Points do not exist within this warehouse.
            throw std::invalid_argument("Starting point or goal are not valid within the warehouse");
        }

        Connection_ptr goalConnection = warehouse.findConnectionFor(goal);
        if (goalConnection == NULL)
        {
            // should never happen.
            throw std::invalid_argument("Goal is not valid within the warehouse");
        }

        std::vector<Path> allPaths;
        std::cout << "Starting path calculations " << std::endl;

        // We construct the initial paths.
        for (const Point& neighbour : findNeighbours(start))
        {
            Path aPath;
            aPath.push_back(start);
            aPath.push_back(neighbour);
            allPaths.push_back(aPath);
        }

        if (allPaths.empty())
        {
            Path aPath;
            aPath.push_back(start);
            return aPath;
        }

        // Now we will keep constructing new paths for each neighbour of the end point of the inital paths.
        // After that, repeat but for the new collection of paths.
        unsigned int pathsAtDestination = 0;
        while (pathsAtDestination != allPaths.size())
        {
            // We clear all paths, to get rid of any non valid ones.
            // We have stored the existing paths to a temp variable, which we will parse for new valid paths.
            std::vector<Path> tempPaths = allPaths;
            allPaths.clear();

            pathsAtDestination = 0;
            for (Path path : tempPaths)
            {
                Point lastPoint = path.getLast();

                // Check if this path has reached it's goal.
                // Once it has, we will return this path as it is the shortest route (least intersections)
                // Reached goal if:
                // 1) last point is same as goal
                // 2) last point is same as goalConnection.one and not goalConnection.two
                // 3) last point is same as goalConnection.two and not goalConnection.one
                if (lastPoint == goal || (lastPoint == goalConnection->one && (goal != goalConnection->two))
                        || (lastPoint == goalConnection->two && (goal != goalConnection->one)))
                {
                    // this path is at its destination.
                    if (fewestIntersections)
                    {
                         return path;
                    }
                    allPaths.push_back(path);
                    ++pathsAtDestination;
                    continue;
                }

                // Construct new paths for each neighbour of the lastpoint in this path
                std::vector<Point> neighbours = findNeighbours(lastPoint);
                if (neighbours.size() > 0)
                {
                    for (const Point& neighbour : neighbours)
                    {
                        // Only add the path if it has valid neighbours
                        // Invalid neighbours are:
                        // - Dead ends
                        // - Cycle paths
                        if (!path.pointInPath(neighbour))
                        {
                            // Copy the path and add the neighbour to it.
                            Path newPath(path);
                            newPath.push_back(neighbour);
                            allPaths.push_back(newPath);
                        }
                    }
                }
            }

            if (allPaths.empty())
            {
                break;
            }
        }

        // should never get here, but just in case it does, we will find the shortest path and return that.

        if (allPaths.size() == 0)
        {
            std::cout << "All paths are empty" << std::endl;
            // either an invalid point has been given or this point does not have any connections. Return an empty path.
            Path dummyPath;
            return dummyPath;
        }

        Path shortestPath = *allPaths.begin();

        for (Path path : allPaths)
        {
            if (path.getLast() == goal || (path.getLast() == goalConnection->one && (goal != goalConnection->two))
                || (path.getLast() == goalConnection->two && (goal != goalConnection->one)))

            {
            if (path.getLength() < shortestPath.getLength())
            {
                shortestPath = path;
            }
            }
            else
            {
            std::cout << "INVALID PATH - DOES NOT REACH THE GOAL" << std::endl;
            }
        }
        std::cout << "Returning the shortest path" << std::endl;
        return shortestPath;
    }

    std::vector<Point> AStar::findNeighbours(const Car::Point& aPoint)
    {
        return warehouse.findNeighbours(aPoint);
    }

} /* namespace Car */

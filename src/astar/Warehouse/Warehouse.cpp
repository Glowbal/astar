/*
 * Warehouse.cpp
 *
 *  Created on: 10 dec. 2014
 *      Author: Thomas
 */

#include "Warehouse.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include "../Path.h"
#include "../Logger.hpp"

namespace Car
{

    Warehouse::Warehouse(const std::string& fileName) :
        name(fileName)
    {
    load(fileName);
    }

    Warehouse::Warehouse(const Warehouse& wh) :
        connections(wh.connections), name(wh.name)
    {

    }

    Warehouse::Warehouse(const std::string& aName, const std::vector<std::shared_ptr<Connection>>& someConnections) :
        connections(someConnections), name(aName)
    {
    }

    Warehouse::~Warehouse()
    {

    }

    std::vector<std::shared_ptr<Connection>> Warehouse::getConnections() const
    {
    return connections;
    }

    void Warehouse::load(const std::string& fileName)
    {
    connections.clear();

    std::ifstream file(fileName);
    std::string line;
    while (std::getline(file, line))
    {
        try
        {
        connections.push_back(stringToConnection(line));
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

    void Warehouse::print() const
    {
    std::cout << "printing all connections. Total: " << connections.size() << std::endl;
    for (std::shared_ptr<Connection> connection : connections)
    {
        if (std::dynamic_pointer_cast<Corner>(connection) != NULL)
        {
        std::shared_ptr<Corner> corner = std::dynamic_pointer_cast<Corner>(connection);
        std::cout << "Connection: ONE: " << corner->one.x << " " << corner->one.y << " TWO: " << corner->two.x << " " << corner->two.y << " "
                << "THREE: " << corner->middle.x << " " << corner->middle.y << " " << std::endl;
        }
        else
        {
        std::cout << "Connection: ONE: " << connection->one.x << " " << connection->one.y << " TWO: " << connection->two.x << " "
                << connection->two.y << " " << std::endl;
        }
    }
    std::cout << "Finished printing all connections" << std::endl;
    }

    std::vector<Point> Warehouse::findNeighbours(const Car::Point& aPoint) const
    {
    std::vector<Point> neighbours;
    for (Connection_ptr con : connections)
    {
        if (con->one == aPoint)
        {
        neighbours.push_back(con->two);
        }
        else if (con->two == aPoint)
        {
        neighbours.push_back(con->one);
        }
    }
    return neighbours;
    }

    Connection_ptr Warehouse::findConnectionFor(const Car::Point& aPoint) const
    {
    for (const Connection_ptr con : connections)
    {
        // TODO Also handle corners correctly
        if (con->isInBetween(aPoint))
        {
        return con;
        }
    }
    return NULL;
    }

    bool Warehouse::isValidPoint(const Car::Point& aPoint) const
    {
    for (const Connection_ptr con : connections)
    {
        // TODO Also handle corners correctly
        if (con->isInBetween(aPoint))
        {
        return true;
        }
    }
    return false;
    }

    bool Warehouse::isValidPath(const Car::Path& aPath) const
    {
    for (const Point& point : aPath.getAllPoints())
    {
        if (!isValidPoint(point))
        {
        return false;
        }
    }
    return true;
    }

    unsigned short Warehouse::getDistanceBetween(const Car::Point& first, const Car::Point& second) const
    {
    return getConnection(first, second)->getLenght();
    }

    std::shared_ptr<Connection> Warehouse::getConnection(const Car::Point& first, const Car::Point& second) const
    {
    for (const Connection_ptr con : connections)
    {
//        if (con->isInBetween(first) && con->isInBetween(second))
//        {
//        return con;
//        }

        if ((con->one == first && con->two == second) || (con->one == second && con->two == first))
        {
        return con;
        }
    }
    std::stringstream error;
    error << "Not a connection in warehouse: " << first.x << " " << first.y << " " << second.x << " " << second.y;
    throw std::invalid_argument(error.str());
    }

    /* Static */std::shared_ptr<Connection> Warehouse::stringToConnection(const std::string& line)
    {
    // TODO Parsing does not function well when retrieving floats from the file.
    // Using float to retrieve the values does not sort this.
    // We might need to consider separators or using Boost Regex instead.
    std::stringstream theLine(line);
    unsigned short position_x = 0;
    unsigned short position_y = 0;

    // TODO Find alternative for using continue. Does not match our style guide.
    if (!(theLine >> position_x >> position_y))
    {
        throw std::invalid_argument("Invalid line, cannot convert to connection");
    }

    Point pointOne(position_x, position_y);
    if (!(theLine >> position_x >> position_y))
    {
        throw std::invalid_argument("Invalid line, cannot convert to connection");
    }
    Point pointTwo(position_x, position_y);
    if (!(theLine >> position_x >> position_y))
    {
        std::shared_ptr<Connection> connection(new Connection(pointOne, pointTwo));
        return connection;
    }
    Point pointThree(position_x, position_y);
    std::shared_ptr<Corner> corner(new Corner(pointOne, pointTwo, pointThree));
    return corner;
    }

    std::string Warehouse::getName() const
    {
    return name;
    }

    Point Warehouse::getLastFacingPoint(const Car::Path& aPath) const
    {
    std::vector<Point> points = aPath.getAllPoints();
    if (points.empty())
    {
        throw std::invalid_argument("Cannot get facing point from empty path");
    }

    Point beforeLast(points.back());
    Point lastFacing(points.back());
    if (points.size() >= 2)
    {
        beforeLast = points.at(points.size() - 2);
        std::vector<Point> neighbours = findNeighbours(points.back());

        switch (beforeLast.findFacingDirection(points.back()))
        {
        case 0:
        {
            // Facing down
            for (const Point& p : neighbours)
            {
            if (p.y < points.back().y)
            {
                lastFacing = p;
                break;
            }
            }
            break;
        }
        case 1:
        {
            // Facing up
            for (const Point& p : neighbours)
            {
            if (p.y > points.back().y)
            {
                lastFacing = p;
                break;
            }
            }
            break;
        }
        case 2:
        {
            // Facing right
            for (const Point& p : neighbours)
            {
            if (p.x > points.back().x)
            {
                lastFacing = p;
                break;
            }
            }
            break;
        }
        case 3:
        {
            // Facing left
            for (const Point& p : neighbours)
            {
            if (p.x < points.back().x)
            {
                lastFacing = p;
                break;
            }
            }
            break;
        }
        default:
        {
            // error, should never get here.
            std::cout << "Invalid direction" << std::endl;
            break;
        }
        }
    }
    return lastFacing;
    }

    Point Warehouse::getNearestValidPoint(const Car::Point& aPoint) const
    {
    if (!connections.empty())
    {
        Point nearestPoint(0, 0);
        nearestPoint = connections.at(0)->one;
        for (const Connection_ptr con : connections)
        {
        float deltaToPointX = aPoint.x - con->one.x;
        float deltaToPoinY = aPoint.y - con->one.y;

        float deltaConX = con->two.x - con->one.x;
        float deltaConY = con->two.y - con->one.y;

        float dot = deltaToPointX * deltaConX + deltaToPoinY * deltaConY;
        float len_sq = deltaConX * deltaConX + deltaConY * deltaConY;
        float param = dot / len_sq;

        unsigned short finalX = 0;
        unsigned short finalY = 0;

        if (param < 0)
        {
            finalX = con->one.x;
            finalY = con->one.y;
        }
        else if (param > 1)
        {
            finalX = con->two.y;
            finalY = con->two.y;
        }
        else
        {
            finalX = con->one.x + param * deltaConX;
            finalY = con->one.y + param * deltaConY;
        }
        Point comparePoint(finalX, finalY);
        if (comparePoint.distanceTo(aPoint) < nearestPoint.distanceTo(aPoint))
        {
            nearestPoint = comparePoint;
        }
        }
        return nearestPoint;
    }
    return aPoint;
    }

    Point Warehouse::getNearestConnectionPoint(const Car::Point& aPoint) const
    {
    if (!connections.empty())
    {
        Point nearestPoint(0, 0);
        nearestPoint = connections.at(0)->one;
        for (const Connection_ptr con : connections)
        {
        float deltaToPointX = aPoint.x - con->one.x;
        float deltaToPoinY = aPoint.y - con->one.y;

        float deltaConX = con->two.x - con->one.x;
        float deltaConY = con->two.y - con->one.y;

        float dot = deltaToPointX * deltaConX + deltaToPoinY * deltaConY;
        float len_sq = deltaConX * deltaConX + deltaConY * deltaConY;
        float param = dot / len_sq;

        unsigned short finalX = 0;
        unsigned short finalY = 0;

        if (param <= 0.5)
        {
            finalX = con->one.x;
            finalY = con->one.y;
        }
        else
        {
            finalX = con->two.y;
            finalY = con->two.y;
        }

        Point comparePoint(finalX, finalY);
        if (comparePoint.distanceTo(aPoint) < nearestPoint.distanceTo(aPoint))
        {
            nearestPoint = comparePoint;
        }
        }
        if (isValidPoint(nearestPoint))
        {
        Logger::log("A valid point");
        }
        else
        {
        Logger::log("a non valid point");
        }
        Logger::log(nearestPoint.asString());

        return nearestPoint;
    }
    return aPoint;
    }

    void Warehouse::operator=(const Warehouse& rhs)
    {
    if (&rhs != this)
    {
        connections = rhs.connections;
        name = rhs.name;
    }
    }

    void Warehouse::operator=(const std::shared_ptr<Warehouse> rhs)
    {
    if ((Warehouse*) &rhs != this)
    {
        connections = rhs->connections;
        name = rhs->name;
    }
    }
} /* namespace Car */

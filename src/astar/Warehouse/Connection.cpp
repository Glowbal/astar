/*
 * Connection.cpp
 *
 *  Created on: 10 dec. 2014
 *      Author: Thomas
 */

#include "Connection.h"
#include <cmath>
#include <cstdlib>
#include <iostream>
#include "../Logger.hpp"

namespace Car
{
    Connection::Connection(Point aPointOne, Point aPointTwo) :
        one(aPointOne), two(aPointTwo)
    {
    }

    Connection::~Connection()
    {
    }

    unsigned short Connection::getLenght() const
    {
        unsigned short diffX = std::abs(one.x - two.x);
        unsigned short diffY = std::abs(one.y - two.y);

        return sqrt(diffX * diffX + diffY * diffY);
    }

    bool Connection::isInBetween(const Point& aPoint) const
    {
        if (one == aPoint || two == aPoint)
        {
            return true;
        }

        unsigned short distanceToFromOne = one.distanceTo(aPoint);
        unsigned short distanceToFromTwo = two.distanceTo(aPoint);

        signed short radian = std::atan2(std::abs(one.y - two.y), std::abs(one.x - two.x));
        signed short angleInDegrees = (radian * 180 / PI);

        Point compareOne((one.x + std::cos(angleInDegrees) * distanceToFromOne), one.y + (std::sin(angleInDegrees) * distanceToFromOne));
        Point compareTwo((two.x - std::cos(angleInDegrees) * distanceToFromTwo), two.y - (std::sin(angleInDegrees) * distanceToFromTwo));

        return compareOne == aPoint && compareTwo == aPoint;
    }

    std::string Connection::asString() const
    {
        std::stringstream stream;
        stream << one.asString() << " " << two.asString();
        return stream.str();
    }
} /* namespace Car */

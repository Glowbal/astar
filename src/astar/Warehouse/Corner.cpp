/*
 * Corner.cpp
 *
 *  Created on: Dec 12, 2014
 *      Author: Jaime
 */

#include "Corner.h"
#include <cmath>
#include <cstdlib>
#include <sstream>

namespace Car
{

    Corner::Corner(Point aPointOne, Point aPointTwo, Point aPointThree) :
        Connection(aPointOne, aPointTwo), middle(aPointThree)
    {
    }

    Corner::~Corner()
    {
    }

    unsigned short Corner::getLength() const
    {
    return Connection(one, middle).getLenght() + Connection(two, middle).getLenght();
    }

    bool Corner::isInBetween(const Point& aPoint) const
    {
    return Connection(one, middle).isInBetween(aPoint) || Connection(two, middle).isInBetween(aPoint);
    }

    std::string Corner::asString() const
    {
    std::stringstream stream;
    stream << one.x << " " << one.y << " " << two.x << " " << two.y << " " << middle.x << " " << middle.y;
    return stream.str();
    }

} /* namespace Car */

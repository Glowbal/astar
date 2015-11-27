/*
 * Point.cpp
 *
 *  Created on: 10 dec. 2014
 *      Author: Thomas
 */

#include "Point.h"
#include <cmath>
#include <cstdlib>
#include <sstream>

namespace Car
{

    Point::Point(unsigned short anX, unsigned short anY) :
        x(anX), y(anY)
    {

    }

    Point::~Point()
    {

    }

    Point::Point(const Point& aPoint) :
        x(aPoint.x), y(aPoint.y)
    {

    }

    void Point::operator=(const Point& aPoint)
    {
    if (&aPoint != this)
    {
        x = aPoint.x;
        y = aPoint.y;
    }
    }
    bool Point::operator==(const Point& aPoint) const
    {
    return (aPoint.x == x && aPoint.y == y);
    }
    bool Point::operator!=(const Point& aPoint) const
    {
    return !operator==(aPoint);
    }

    unsigned short Point::distanceTo(const Point& aPoint) const
    {
    unsigned short diffX = std::abs(x - aPoint.x);
    unsigned short diffY = std::abs(y - aPoint.y);

    return std::abs(sqrt(diffX*diffX + diffY*diffY));
    }

    unsigned char Point::findFacingDirection(const Point& facing) const
    {
    // find the direction that the robot is facing based on the current and previous point.
    unsigned char directionFacing = 1;
    if (y > facing.y && x == facing.x)
    {
        // facing down
        directionFacing = 0;
    }
    else if (x < facing.x && y == facing.y)
    {
        // facing right
        directionFacing = 2;
    }
    else if (x > facing.x && y == facing.y)
    {
        // facing left
        directionFacing = 3;
    } // default is 1, which is facing up. No need to handle.
    return directionFacing;
    }

    std::string Point::asString() const
    {
    std::stringstream stream;
    stream << x << " " << y;
    return stream.str();
    }

} /* namespace Car */

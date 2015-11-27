/*
 * Path.cpp
 *
 *  Created on: 11 dec. 2014
 *      Author: Thomas
 */

#include "Path.h"
#include <iostream>

namespace Car
{

    Path::Path() :
        lastDirection(0, 0), currentPosition(0)
    {
    }

    Path::~Path()
    {
    }

    Path::Path(const Path& aPath) :
        allPoints(aPath.allPoints), lastDirection(aPath.lastDirection), currentPosition(0)
    {

    }

    void Path::push_back(const Point& aPoint)
    {
    allPoints.push_back(aPoint);
    }

    void Path::next()
    {
    if (currentPosition < allPoints.size())
    {
        ++currentPosition;
    }

    }

    std::vector<Point>::const_iterator Path::begin() const
    {
    return allPoints.begin();
    }

    Point Path::front() const
    {
    return *begin();
    }

    Point Path::getCurrent() const
    {
    if (currentPosition < allPoints.size())
    {
        return allPoints.at(currentPosition);
    }
    return allPoints.back();
    }

    bool Path::pointInPath(const Point& aPoint) const
    {
    for (const Point& comparePoint : allPoints)
    {
        if (aPoint == comparePoint)
        {
        return true;
        }
    }
    return false;
    }

    unsigned short Path::getLength() const
    {
    unsigned short length = 0;

    for (unsigned int i = 0; i < allPoints.size(); ++i)
    {
        if (i != allPoints.size() - 1)
        {
        length += allPoints[i].distanceTo(allPoints[i + 1]);
        }
    }
    return length;
    }

    Point Path::getLast() const
    {
    if (allPoints.empty())
    {
        Point aPoint(0, 0);
        return aPoint;
    }
    return allPoints.back();
    }

    void Path::print() const
    {
    for (const Point& aPoint : allPoints)
    {
        std::cout << "POINT: " << aPoint.x << " " << aPoint.y << std::endl;
    }
    }

    std::vector<Point> Path::getAllPoints() const
    {
    return allPoints;
    }

    Path& Path::operator+=(const Path &rhs)
    {
    if (rhs.allPoints.size() > 0)
    {
        bool skip = false;
        if (!allPoints.empty())
        {
        if (allPoints.back() == rhs.allPoints.front())
        {
            skip = true;
        }
        }

        for (const Point& aPoint : rhs.allPoints)
        {
        if (!skip)
        {
            allPoints.push_back(aPoint);
        }
        else
        {
            skip = false;
        }
        }
    }
    return *this;
    }

} /* namespace Car */

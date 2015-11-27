/*
 * Corner.h
 *
 *  Created on: Dec 12, 2014
 *      Author: Jaime
 */

#ifndef CORNER_H_
#define CORNER_H_

#include "Point.h"
#include "Connection.h"

namespace Car
{

    class Corner: public Connection
    {
    public:
        Corner(Point aPointOne, Point aPointTwo, Point aPointThree);
        virtual ~Corner();

        /**
         * Get the length of this connection.
         * @return Distance in cm between Point One and Point Two.
         */
        unsigned short getLength() const;

        /**
         * Check if the given point is in between the points one and two of this connection.
         * @param aPoint The point.
         * @return True if the point is in between the connection points.
         */
        bool isInBetween(const Point& aPoint) const;

        /**
         * Get the connection as a string representation.
         * Sample: "50 50 100 100 25 25" (one.x one.y two.x two.y three.x three.y).
         * @return string representation of the corner.
         */
        std::string asString() const;

        Point middle;

    };

} /* namespace Car */

#endif /* CORNER_H_ */

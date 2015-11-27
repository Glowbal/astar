/*
 * Connection.h
 *
 *  Created on: 10 dec. 2014
 *      Author: Thomas
 */

#ifndef CONNECTION_H_
#define CONNECTION_H_

#include "Point.h"
#include <memory>
#include <sstream>
#define PI 3.14159265

namespace Car
{

    class Connection
    {
    public:
        Connection();
        Connection(Point aPointOne, Point aPointTwo);
        virtual ~Connection();

        /**
         * Get the length of this connection.
         * @return Distance in cm between Point One and Point Two.
         */
        unsigned short getLenght() const;

        /**
         * Check if the given point is in between the points one and two of this connection.
         * @param aPoint The point.
         * @return True if the point is in between the connection points.
         */
        bool isInBetween(const Point& aPoint) const;

        /**
         * Get the connection as a string representation.
         * Sample: "50 50 100 100" (one.x one.y two.x two.y).
         * @return string representation of the connection.
         */
        std::string asString() const;

        Point one;
        Point two;

    };
    typedef std::shared_ptr<Connection> Connection_ptr;
} /* namespace Car */

#endif /* CONNECTION_H_ */

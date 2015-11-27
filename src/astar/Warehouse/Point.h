/*
 * Point.h
 *
 *  Created on: 10 dec. 2014
 *      Author: Thomas
 */

#ifndef POINT_H_
#define POINT_H_

#include <string>

namespace Car
{

    class Point
    {
    public:
        Point(unsigned short anX, unsigned short anY);
        virtual ~Point();

        Point(const Point& aPoint);
        void operator=(const Point& aPoint);
        bool operator==(const Point& aPoint) const;
        bool operator!=(const Point& aPoint) const;

        /**
         * Calculate the distance from this point to another.
         * @param aPoint
         * @return distance.
         */
        unsigned short distanceTo(const Point& aPoint) const;

        /**
         * Find which direction the given point is relative from this point.
         * @param aPoint.
         * @return Facing direction. 0 = down, 1 = up, 2 = right, 3 = left.
         */
        unsigned char findFacingDirection(const Point& facing) const;

        /*
         * Get this point as a string
         */
        std::string asString() const;

        unsigned short x;
        unsigned short y;
    };

} /* namespace Car */

#endif /* POINT_H_ */

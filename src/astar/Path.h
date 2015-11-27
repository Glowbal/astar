/*
 * Path.h
 *
 *  Created on: 11 dec. 2014
 *      Author: Thomas
 */

#ifndef PATH_H_
#define PATH_H_

#include "Warehouse/Point.h"
#include <memory>
#include <vector>

namespace Car
{

    class Path
    {
    public:
        Path();
        virtual ~Path();

        /**
         * Copy constructor.
         */
        Path(const Path& aPath);

        /**
         * Add a new point to the end of this path.
         */
        void push_back(const Point& aPoint);

        /**
         * Increase the pointer for the current path.
         */
        void next();

        /**
         * Get the iterator to the first point of this path.
         *
         * @return Iterator.
         */
        std::vector<Point>::const_iterator begin() const;

        /**
         * Get the first point in this path.
         *
         * @return first point of the path.
         */
        Point front() const;

        /**
         * Get the current point of the path. This is increased through the usage of
         * the next() function call.
         *
         * @return The current point of the path.
         */
        Point getCurrent() const;

        /**
         * Check if point exist within this path.
         */
        bool pointInPath(const Point& aPoint) const;

        /**
         * Get the total length of path in centimeters.
         * @return length of path in centimeters.
         */
        unsigned short getLength() const;

        /**
         * Get the last point in this path.
         * @return last point in path. Returns a point with 0,0 if no points have been added.
         */
        Point getLast() const;

        /**
         * Print all points in this path in the order they have been added in.
         */
        void print() const;

        /**
         * Grab all points from the Path.
         * @return All points in the path.
         */
        std::vector<Point> getAllPoints() const;

        /**
         * Combine two paths.
         */
        Path& operator+=(const Path &rhs);

    private:
        std::vector<Point> allPoints;
        Point lastDirection;
        unsigned long currentPosition;

    };

} /* namespace Car */

#endif /* PATH_H_ */

/*
 * Warehouse.h
 *
 *  Created on: 10 dec. 2014
 *      Author: Thomas
 */

#ifndef WAREHOUSE_H_
#define WAREHOUSE_H_

#include "Connection.h"
#include "Corner.h"
#include <vector>
#include <string>
#include <memory>

namespace Car
{
    class Path;

    class Warehouse
    {
    public:
        Warehouse(const std::string& fileName);
        Warehouse(const Warehouse& wh);
        Warehouse(const std::string& aName, const std::vector<std::shared_ptr<Connection>>& someConnections);
        virtual ~Warehouse();

        /**
         * Retrieve all connections from the warehouse.
         */
        std::vector<std::shared_ptr<Connection>> getConnections() const;

        /**
         * Load a warehouse file.
         * @param fileName The file that will be loaded.
         */
        void load(const std::string& fileName);

        /**
         * Print all connections from the warehouse to the output stream.
         */
        void print() const;

        /**
         * Find the neighbours of a point.
         * @param aPoint The point for which the neighbours will be searched.
         * @return a Vector containing neighbour points.
         */
        std::vector<Point> findNeighbours(const Car::Point& aPoint) const;

        /**
         * Find a matching connection for the point.
         * @param aPoint.
         *
         * @return A shared_ptr to a connection.
         */
        Connection_ptr findConnectionFor(const Car::Point& aPoint) const;

        /**
         * Check if the given point is a valid point within the warehouse.
         * @param aPoint the point that will be checked against all points in the warehouse.
         *
         * @return True if point is a valid point.
         */
        bool isValidPoint(const Car::Point& aPoint) const;

        /**
         * Check if path is valid for this warehouse.
         * @param a Path.
         */
        bool isValidPath(const Car::Path& aPath) const;

        /**
         * Get the distance between two points.
         * @param first.
         * @param second.
         * @return the distance.
         */
        unsigned short getDistanceBetween(const Car::Point& first, const Car::Point& second) const;

        /**
         * Get the connection matching both points.
         * @param first.
         * @param second.
         * @return The connection.
         */
        Connection_ptr getConnection(const Car::Point& first, const Car::Point& second) const;

        /**
         * Convert a string to a connection.
         * @exception invalid_argument
         * @param line. In format: x y x y (x y) Last x and y are optional for corners.
         *
         * @return pointer to a connection or corner.
         */
        static Connection_ptr stringToConnection(const std::string& line);

        /**
         * @return the name of the warehouse
         */
        std::string getName() const;

        /**
         * Find the point that a robot would be facing last for a given path.
         * @param aPath.
         * @return point.
         */
        Point getLastFacingPoint(const Car::Path& aPath) const;

        /**
         * Get the nearest valid point within this warehouse.
         * @param aPoint.
         * @return Nearest valid point.
         */
        Point getNearestValidPoint(const Car::Point& aPoint) const;

        /**
         * Get the nearest connection point (an intersection or end of line).
         * @param aPoint.
         * @return <earest valid connection point.
         */
        Point getNearestConnectionPoint(const Car::Point& aPoint) const;

        /**
         *
         */
        void operator=(const Warehouse& rhs);

        /**
         *
         */
        void operator=(std::shared_ptr<Warehouse> rhs);

    private:
        std::vector<std::shared_ptr<Connection>> connections;

        /**
         * The name of the warehouse
         */
        std::string name;
    };

    typedef std::shared_ptr<Car::Warehouse> WarehousePtr;
    typedef std::vector<WarehousePtr> WarehousePtrs;

} /* namespace Car */

#endif /* WAREHOUSE_H_ */

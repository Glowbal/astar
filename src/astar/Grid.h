/*
 * Grid.h
 *
 *  Created on: 10 dec. 2014
 *      Author: Thomas
 */

#ifndef Grid_H_
#define Grid_H_

#include "Node.h"
#include <vector>
#include <string>
#include <memory>

namespace HAN
{
    class Grid
    {
    public:
        Grid(const std::string& fileName);
        Grid(const Grid& wh);
        Grid(const std::string& aName, const NodePtrs& someNodes);
        virtual ~Grid();

        void load(const std::string& fileName);

        NodePtrs GetNodes();

        bool isValidNode(NodePtr aNode);

        NodePtrs findNeighbours(NodePtr aNode);

        void print(NodePtrs aPath);

        void resetGrid();

        /**
         *
         */
        void operator=(const Grid& rhs);

        /**
         *
         */
        void operator=(std::shared_ptr<Grid> rhs);

    private:
        NodePtrs nodes;

        /**
         * The name of the Grid
         */
        std::string name;
    };

    typedef std::shared_ptr<HAN::Grid> GridPtr;
    typedef std::vector<GridPtr> GridPtrs;

} /* namespace HAN */

#endif /* Grid_H_ */

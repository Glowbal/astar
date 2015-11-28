/*
 * Node.h
 *
 *  Created on: 10 dec. 2014
 *      Author: Thomas
 */

#ifndef Node_H_
#define Node_H_

#include <string>
#include <vector>
#include <memory>

namespace HAN
{
    class Node
    {
    public:
        Node(unsigned short anX, unsigned short anY);
        virtual ~Node();

        Node(const Node& aNode);
        void operator=(const Node& aNode);
        bool operator==(const Node& aNode) const;
        bool operator!=(const Node& aNode) const;

        /**
         * Calculate the distance from this Node to another.
         * @param aNode
         * @return distance.
         */
        unsigned short distanceTo(const Node& aNode) const;

        /*
         * Get this Node as a string
         */
        std::string asString() const;

        bool accessable;
        unsigned short x;
        unsigned short y;
        unsigned short cost;
        unsigned short heuristicValue;
        unsigned short fValue;
        std::shared_ptr<HAN::Node> parentNode;
    };
    typedef std::shared_ptr<HAN::Node> NodePtr;
    typedef std::vector<NodePtr> NodePtrs;
} /* namespace HAN */

#endif /* Node_H_ */

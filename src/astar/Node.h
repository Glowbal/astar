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
        Node(float anX, float anY);
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
        float distanceTo(const Node& aNode) const;

        /*
         * Get this Node as a string
         */
        std::string asString() const;

        bool accessable;
        float x;
        float y;
        float cost;
        float heuristicValue;
        float fValue;
        std::shared_ptr<HAN::Node> parentNode;
    };
    typedef std::shared_ptr<HAN::Node> NodePtr;
    typedef std::vector<NodePtr> NodePtrs;
} /* namespace HAN */

#endif /* Node_H_ */

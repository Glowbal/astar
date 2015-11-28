/*
 * Node.cpp
 *
 *  Created on: 10 dec. 2014
 *      Author: Thomas
 */

#include "Node.h"
#include <cmath>
#include <cstdlib>
#include <sstream>

namespace HAN
{

    Node::Node(unsigned short anX, unsigned short anY) :
        x(anX), y(anY), cost(0), heuristicValue(0), fValue(0)
    {
        accessable = true;
    }

    Node::~Node()
    {

    }

    Node::Node(const Node& aNode) :
        x(aNode.x), y(aNode.y), cost(aNode.cost)
    {

    }

    void Node::operator=(const Node& aNode)
    {
        if (&aNode != this)
        {
            x = aNode.x;
            y = aNode.y;
            cost = aNode.cost;
        }
    }
    bool Node::operator==(const Node& aNode) const
    {
        return (aNode.x == x && aNode.y == y && aNode.cost == cost);
    }
    bool Node::operator!=(const Node& aNode) const
    {
        return !operator==(aNode);
    }

    unsigned short Node::distanceTo(const Node& aNode) const
    {
        unsigned short horizontalDiff = std::abs(x - aNode.x);
        unsigned short verticalDiff = std::abs(y - aNode.y);

        return horizontalDiff + verticalDiff;
    }

    std::string Node::asString() const
    {
        std::stringstream stream;
        stream << x << " " << y;
        return stream.str();
    }

} /* namespace HAN */

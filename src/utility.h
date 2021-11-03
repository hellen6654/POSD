#ifndef UTILITY_H
#define UTILITY_H

#include <deque>
#include "node.h"
#include "iterator.h"
#include "node_iterator.h"
class SizeFilter
{
public:
    SizeFilter(double upperBound, double lowerBound)
    {
        _up = upperBound;
        _low = lowerBound;
    }
    bool operator()(Node *node) const
    {
        return node->size() <= _up && node->size() >= _low;
    }

private:
    double _up, _low;
};

template <class Filter>
std::deque<Node *> filterNode(Node *node, Filter filter)
{
    // access the node with iterator pattern.
    // DO NOT use Type Checking or Dynamic Type that would violate OCP to implement the function.
    // return the nodes under the input node tree sturctur that match the given filter.
    // throw std::string "Only folder can filter node!" when the input node is not iterable.
    std::deque<Node *> result;

    Iterator *it = node->createIterator();

    if (it->isDone())
        throw std::string("Only folder can filter node!");

    while (!it->isDone())
    {
        //std::cout << it->currentItem()->info() << std::endl;
        if (filter(it->currentItem()))
        {
            //Normal shape
            result.push_back(it->currentItem());
        }
        if (!(it->currentItem()->createIterator()->isDone()))
        {
            //CompoundShape
            std::deque<Node *> temp = filterNode(it->currentItem(), filter);
            for (auto it : temp)
                result.push_back(it);
        }
        it->next();
    }
    return result;
}

#endif
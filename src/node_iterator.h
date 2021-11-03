#ifndef NODE_ITERATOR_H
#define NODE_ITERATOR_H
#include "iterator.h"
#include "node.h"

template<class ForwardIterator>
class NodeIterator : public Iterator {
public:
    NodeIterator(ForwardIterator begin, ForwardIterator end) {
        // initialize iterator.
        _begin = begin;
        _end = end;
        _currentItem = begin;
    }
    
    void first() {
        // initialize iterator.
        _currentItem = _begin;
    }
    
    void next() {
        // move iterator to next position,
        // throw std::string "Moving past the end!" when iterator move over the range of the structure.
        if(_currentItem == _end)
            throw std::string ("Moving past the end!");
        _currentItem++;
    }
    
    bool isDone() const {
        // return true when iterator reach the end of the structure.
        return _currentItem == _end;
    }
    
    Node* currentItem() const {
        // return the Node that iterator currently point at.
        return *_currentItem;
    }
private:
    ForwardIterator _begin,_end,_currentItem;
};
#endif
#ifndef SHAPE_ITERATOR_H
#define SHAPE_ITERATOR_H
#include "iterator.h"

template<class ForwardIterator>
class ShapeIterator : public Iterator 
{
public:
    ShapeIterator(ForwardIterator begin, ForwardIterator end)
    { 
        _begin = begin;
        _end=end;
        _current = begin;
    }
    
    void first() 
    {
        // initialize iterator.
        _current = _begin;
    }
    
    void next() 
    {
        // move iterator to next position,
        // throw std::string "Moving past the end!" when iterator move over the range of the structure.
        if((_current) == _end)
            throw std::string ("Moving past the end!");
        _current++;
        
    }
    
    bool isDone() const 
    {
        return _current == _end;
    }
    
    Shape* currentItem() const 
    {
        // return the shape that iterator currently point at.
        //maybe have bug
        return *_current;
    }
private:
    ForwardIterator _begin,_end,_current;
};

#endif
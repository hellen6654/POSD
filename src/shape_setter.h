#pragma once
#include "filter.h"

typedef void (*Setter)(Shape *shape);

class ShapeSetter : public Filter
{
public:
    ShapeSetter(Setter set): _setter(set),_nextFilter(nullptr) {}
    // `Setter` is a template name for lambda,
    //  you may use your own name.

    Filter *setNext(Filter *filter)
    {
        // seeting next filter.
        _nextFilter = filter;
        return filter;
    }

    std::list<Shape *> push(std::list<Shape *> shapes)
    {
        // push down setted data and return result.
        for(auto it : shapes)
        {
            _setter(it);
        }

        if (_nextFilter)
        {
            shapes = _nextFilter->push(shapes);
        }
        
        return shapes;
    }

private:
    Setter _setter;
    Filter *_nextFilter;
};

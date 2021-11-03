#pragma once
#include "filter.h"
#include "shape_iterator.h"

typedef bool (*Predicate)(Shape* shape);

class ShapeFilter : public Filter {
public:

    ShapeFilter(Predicate pred) :_predicate(pred),_nextFilter(nullptr){}
    // `Predicate` is a template name for lambda,
    //  you may use your own name.
        
    Filter* setNext(Filter* filter) 
    {
        // seeting next filter.
        _nextFilter = filter;
        return filter;
    }
    std::list<Shape*> push(std::list<Shape*> shapes) 
    {
        // push down filtered data and return result.
        std::list<Shape*> result;
        for(auto it : shapes)
        {
            if (_predicate(it))
                result.push_back(it);
        }

        if (_nextFilter)
        {
            result = _nextFilter->push(result);
        }

        return result;
    }
private:
    Predicate _predicate;
    Filter* _nextFilter;
};

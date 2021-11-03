#ifndef NULLITERATOR_H
#define NULLITERATOR_H
#include "iterator.h"
class NullIterator : public Iterator {
public:
    void first() {
        // throw std::string "No child member!"
        throw std::string("No child member!");
    }

    void next() {
        // throw std::string "No child member!"
        throw std::string("No child member!");
    }
    
    bool isDone() const {
        // return true
        return true;
    }
    
    Shape* currentItem() const {
        // throw std::string "No child member!"
        throw std::string("No child member!");
    }
};
#endif


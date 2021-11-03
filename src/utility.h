#ifndef UILITY_H
#define UILITY_H
#include <iostream>
#include <deque>
#include "shape.h"
#include "shape_iterator.h"
class AreaFilter
{
public:
    AreaFilter(double upperBound, double lowerBound)
    {
        _upper = upperBound;
        _lower = lowerBound;
    }
    bool operator()(Shape *shape) const
    {
        return (shape->area() >= _lower && shape->area() <= _upper);
    }

private:
    double _upper, _lower;
};

class PerimeterFilter
{
public:
    PerimeterFilter(double upperBound, double lowerBound)
    {
        _upper = upperBound;
        _lower = lowerBound;
    }
    bool operator()(Shape *shape) const
    {
        return (shape->perimeter() >= _lower && shape->perimeter() <= _upper);
    }

private:
    double _upper, _lower;
};

class ColorFilter
{
public:
    ColorFilter(std::string color) { _color = color; }
    bool operator()(Shape *shape) const { return shape->color() == _color; }

private:
    std::string _color;
};

class TypeFilter
{
public:
    TypeFilter(std::string type) { _type = type; }
    bool operator()(Shape *shape) const { return shape->type() == _type; }

private:
    std::string _type;
};

Shape *getShapeById(Shape *shape, std::string id)
{
    // ID will be unique
    // access the shape with iterator pattern.
    // DO NOT use Type Checking or Dynamic Type that would violate OCP to implement the function.
    // return a shape under the input shape tree sturcture that matches the id.
    // throw std::string "Only compound shape can get shape!" when the input shape is not iterable.
    // throw std::string "Expected get shape but shape not found" when no shape found with the given id.
    Iterator *it = shape->createIterator();

    if (it->isDone())
        throw std::string("Only compound shape can get shape!");

    while (!it->isDone())
    {
        if (it->currentItem()->id() == id)
        {
            //Normal shape
            return it->currentItem();
        }
        else if (!it->currentItem()->createIterator()->isDone())
        {
            //Compound shape
            return getShapeById(it->currentItem(), id);
        }
        it->next();
    }

    throw std::string("Expected get shape but shape not found");
}

template <class Filter>
std::deque<Shape *> filterShape(Shape *shape, Filter filter)
{
    // access the shape with iterator pattern.
    // DO NOT use Type Checking or Dynamic Type that would violate OCP to implement the function.
    // return the shapes under the input shape tree sturcture that match the given filter.
    // throw std::string "Only compound shape can filter shape!" when the input shape is not iterable.
    std::deque<Shape *> result;
    Iterator *it = shape->createIterator();

    if (it->isDone())
        throw std::string("Only compound shape can filter shape!");

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
            std::deque<Shape *> temp = filterShape(it->currentItem(), filter);
            for (auto it : temp)
                result.push_back(it);
        }
        
        it->next();
    }
    return result;
}

#endif
#ifndef COMPOUND_SHAPE_H
#define COMPOUND_SHAPE_H

#include <iomanip>
#include <vector>
#include <sstream>
#include <iostream>
#include "shape.h"

class CompoundShape : public Shape
{
public:
    CompoundShape(std::string id, std::vector<Shape *> *shapes)
    {
        // The default color of compound shape should be "transparent".
        // When there's no shape contain in the compound shape,
        // should throw std::string "This is not a compound shape!"
        if (shapes->size() == 0)
        {
            throw std::string("This is not a compound shape!");
        }
        _shapes = shapes;
        _id = id;
        _color = "transparent";
    }

    double area() const
    {
        // return sum of all containing shapes area.
        double result = 0.0;
        std::vector<Shape *>::iterator it;
        for (it = _shapes->begin(); it != _shapes->end(); it++)
        {
            result += (*it)->area();
        }
        return result;
    }

    double perimeter() const
    {
        double result = 0.0;
        std::vector<Shape *>::iterator it;
        for (it = _shapes->begin(); it != _shapes->end(); it++)
        {
            result += (*it)->perimeter();
        }
        return result;
    }

    std::string info() const
    {
        // return list of all containing shapes info with wrapped of "CompoundShape {}".
        // ex."Compound Shape {Ellipse (4.000, 3.000), Rectangle (3.000, 4.000), Triangle ([0.000, 0.000], [3.000, 0.000], [0.000, 4.000])}"
        std::stringstream ss;
        ss << "Compound Shape {";
        std::vector<Shape *>::iterator it;
        for (it = _shapes->begin(); it != _shapes->end(); it++)
        {
            ss << (*it)->info();
            if ((*it) != _shapes->back())
            {
                ss << ", ";
            }
        }
        ss << "}";
        return ss.str();
    }

    void addShape(Shape *shape)
    {
        // add shape into compound shape.
        if (shape != nullptr)
        {
            _shapes->push_back(shape);
        }
    }

    void deleteShapeById(std::string id)
    {
        // search and delete a shape through id,
        // search all the containing shapes and the tree structure below,
        // if no match of id, throw std::string "Expected delete shape but shape not found"
        std::vector<Shape *>::iterator it;
        for (it = _shapes->begin(); it != _shapes->end(); it++)
        {
            try
            {
                if ((*it)->color() == "transparent")
                {
                    (*it)->deleteShapeById(id);
                    return;
                }
            }
            catch (const std::string e)
            {
            }
            if ((*it)->id() == id)
            {
                _shapes->erase(it);
                return;
            }
        }
        throw std::string("Expected delete shape but shape not found");
    }

    Shape *getShapeById(std::string id)
    {
        // search and return a shape through id,
        // search all the containing shapes and the tree structure below,
        // if no match of id, throw std::string "Expected get shape but shape not found"
        std::vector<Shape *>::iterator it;

        for (it = _shapes->begin(); it != _shapes->end(); it++)
        {
            try
            {
                if ((*it)->color() == "transparent")
                {
                    return (*it)->getShapeById(id);
                }
            }
            catch (const std::string e)
            {
            }

            if ((*it)->id() == id)
            {
                return (*it);
            }
        }
        throw std::string("Expected get shape but shape not found");
    }

private:
    std::vector<Shape *> *_shapes;
};

#endif

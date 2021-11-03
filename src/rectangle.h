#ifndef RECTANGLE_H
#define RECTANGLE_H
#include <sstream>
#include "shape.h"

class Rectangle : public Shape
{
public:
    Rectangle(double length, double width)
    {
        // If the rectangle can't be successfully created,
        // handle the exception by throwing string "This is not a rectangle!"

        if (length > 0 && width > 0)
        {
            _length = length;
            _width = width;
        }
        else
        {
            throw std::string("This is not a rectangle!");
        }
    }

    double area() const
    {
        // return the area of the Rectangle.
        return _length * _width;
    }

    double perimeter() const
    {
        // return the perimeter of the Rectangle.
        return _length * 2 + _width * 2;
    }

    std::string info() const
    {
        // return the info of the Rectangle.
        // ex. Rectangle (3.712, 4.000)
        std::stringstream ss;
        ss << std::fixed << std::setprecision(3);
        ss << "Rectangle (" << _length << ", " << _width <<")";
        return ss.str();
    }

private:
    double _length;
    double _width;
};
#endif
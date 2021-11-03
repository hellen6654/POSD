#ifndef RECTANGLE_H
#define RECTANGLE_H
#include <sstream>
#include <iomanip>
#include "shape.h"

class Rectangle : public Shape
{
public:
    Rectangle(){}
    
    Rectangle(std::string id, double length, double width)
    {
        if (IsRectangle(length, width))
        {
            _length = length;
            _width = width;
            _id = id;
            _color = "white";
        }
        else
        {
            throw std::string("This is not a rectangle!");
        }
    }

    Rectangle(std::string id, double length, double width, std::string color)
    {
        if (IsRectangle(length, width))
        {
            _length = length;
            _width = width;
            _id = id;
            _color = color;
        }
        else
        {
            throw std::string("This is not a rectangle!");
        }
    }

    std::string id() { return _id; }

    std::string color() { return _color; }

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
        ss << "Rectangle (" << _length << ", " << _width << ")";
        return ss.str();
    }

private:
    double _length;
    double _width;

    bool IsRectangle(double length, double width) { return length > 0 && width > 0; }
};
#endif
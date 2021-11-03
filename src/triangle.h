#ifndef TRIANGLE_H
#define TRIANGLE_H
#include <vector>
#include <cmath>
#include <sstream>
#include <iomanip>
#include <iostream>
#include "two_dimensional_coordinate.h"
#include "shape.h"

class Triangle : public Shape
{
public:
    Triangle(){}
    
    Triangle(std::string id, std::vector<TwoDimensionalCoordinate *> coordinates)
    {
        if (coordinates.size() == 3 && IsTriangle(coordinates))
        {
            _a = (*coordinates.begin())->Distance(*(coordinates.begin() + 1));       // a to b distance
            _b = (*coordinates.begin())->Distance(*(coordinates.begin() + 2));       // a to c distance
            _c = (*(coordinates.begin() + 1))->Distance(*(coordinates.begin() + 2)); // b to c distance
            _points = coordinates;
            _id = id;
            _color = "white";
        }
        else
        {
            throw std::string("This is not a triangle!");
        }
    }

    Triangle(std::string id, std::vector<TwoDimensionalCoordinate *> coordinates, std::string color)
    {
        if (coordinates.size() == 3 && IsTriangle(coordinates))
        {
            _a = (*coordinates.begin())->Distance(*(coordinates.begin() + 1));       // a to b distance
            _b = (*coordinates.begin())->Distance(*(coordinates.begin() + 2));       // a to c distance
            _c = (*(coordinates.begin() + 1))->Distance(*(coordinates.begin() + 2)); // b to c distance
            _points = coordinates;
            _id = id;
            _color = color;
        }
        else
        {
            throw std::string("This is not a triangle!");
        }
    }

    std::string id() { return _id; }

    std::string color() { return _color; }

    double area() const
    {
        // return the area of the Triangle.
        double s = (_a + _b + _c) / 2.0;
        return std::sqrt(s * (s - _a) * (s - _b) * (s - _c));
    }

    double perimeter() const
    {
        // return the perimeter of the Triangle.
        return _a + _b + _c;
    }

    std::string info() const
    {
        // return the info of the Triangle.
        // ex. Triangle ([0.000, 0.000], [0.000, -3.141], [-4.000, 0.000])
        std::stringstream ss;
        ss << std::fixed << std::setprecision(3);
        std::string result = "Triangle (";
        for (int i = 0; i < 3; i++)
        {
            ss << "[" << _points[i]->getX() << ", " << _points[i]->getY() << "]";
            if (i != 2)
                ss << ", ";
        }
        result += ss.str() + ")";
        return result;
    }

private:
    std::vector<TwoDimensionalCoordinate *> _points; //points
    double _a, _b, _c;                               //edges

    bool IsTriangle(std::vector<TwoDimensionalCoordinate *> vectors)
    {
        double a, b, c;
        a = (*vectors.begin())->Distance(*(vectors.begin() + 1));       // a to b distance
        b = (*vectors.begin())->Distance(*(vectors.begin() + 2));       // a to c distance
        c = (*(vectors.begin() + 1))->Distance(*(vectors.begin() + 2)); // b to c distance
        //任一邊 !=0 與 任兩邊和 > 第三邊
        return (a != 0 && b != 0 && c != 0 && (a + b > c && a + c > b && b + c > a));
    }
};
#endif
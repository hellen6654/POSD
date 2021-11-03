#ifndef TRIANGLE_H
#define TRIANGLE_H
#include <vector>
#include <cmath>
#include <sstream>
#include <iomanip>
#include <iostream>
#include "two_dimensional_coordinate.h"

class Triangle : public Shape
{
public:
    Triangle(std::vector<TwoDimensionalCoordinate*> vectors)
    {
        // If the triangle can't be successfully created,
        // handle the exception by throwing string "This is not a triangle!"
        
        if(vectors.size()!=3)
            throw std::string("This is not a triangle!");

        double edges[3];
        
        for(int i =0;i<3;i++)
        {
            edges[i] = std::sqrt(
            std::pow((vectors[i % 3]->getX()-vectors[(i+1) % 3]->getX()),2) + 
            std::pow((vectors[i % 3]->getY()-vectors[(i+1) % 3]->getY()),2)
            );
        }
        
        if(edges[0]==0 || edges[1]==0 || edges[2]==0 ||
            (edges[0]+edges[1] <= edges[2]||
            edges[0]+edges[2] <= edges[1]||
            edges[1]+edges[2] <= edges[0]))
        { 
            //任一邊=0 或 任兩邊<=第三邊
            throw std::string("This is not a triangle!");
        }
        else 
        {
            //points
            _points = vectors;
            //edges
            _a = edges[0];
            _b = edges[1];
            _c = edges[2];
        }
    }

    double area() const
    {
        // return the area of the Triangle.
        double s = (_a+_b+_c)/2.0;
        return std::sqrt(s*(s-_a)*(s-_b)*(s-_c));
    }

    double perimeter() const
    {
        // return the perimeter of the Triangle.
        return _a+_b+_c;
    }

    std::string info() const
    {
        // return the info of the Triangle.
        // ex. Triangle ([0.000, 0.000], [0.000, -3.141], [-4.000, 0.000])
        std::stringstream ss;
        ss << std::fixed << std::setprecision(3);
        std::string result = "Triangle (";
        for(int i=0;i<3;i++)
        {
            ss << "[" << _points[i]->getX() << ", " << _points[i]->getY() <<"]";
            if(i!=2) ss<<", ";
        }
        result += ss.str()+")";
        return result;
    }
private:
    std::vector<TwoDimensionalCoordinate*> _points; //points
    double _a,_b,_c; //edges
};
#endif
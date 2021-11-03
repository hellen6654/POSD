#include <iostream>
#include <string>
#include <deque>
#include "two_dimensional_coordinate.h"
#include "triangle.h"
#include "ellipse.h"
#include "rectangle.h"
#include "compound_shape.h"
#include "shape.h"

class ShapeBuilder
{
public:
    ShapeBuilder(){}

    void buildRectangle(double length, double width)
    {
        // build a rectangle with an unique id and push in a std::stack.
        
        _result.push_back(new Rectangle(std::to_string(_result.size()), length, width));
    }

    void buildEllipse(double semiMajorAxes, double semiMinorAxes)
    {
        // build a ellipse with an unique id and push in a std::stack.
        _result.push_back(new Ellipse(std::to_string(_result.size()), semiMajorAxes, semiMinorAxes));
    }

    void buildTriangle(double x1, double y1, double x2, double y2, double x3, double y3)
    {
        // build a triangle with an unique id and push in a std::stack.
        std::vector<TwoDimensionalCoordinate *> points{
            new TwoDimensionalCoordinate(x1, y1),
            new TwoDimensionalCoordinate(x2, y2),
            new TwoDimensionalCoordinate(x3, y3)};
        _result.push_back(new Triangle(std::to_string(_result.size()), points));
    }

    void buildCompoundShapeBegin()
    {
        // for notifing beginning of a Compound Shape.
        std::list<Shape *> shapes;
        _result.push_back(new CompoundShape(std::to_string(_result.size()), shapes));
    }

    void buildCompoundShapeEnd()
    {
        // for notifing ending of a Compound Shape.
        std::deque<Shape *> temp;
        Shape *s;
        while (_result.size() > 0)
        {
            s = _result.back();
            _result.pop_back();
            if (s->area() == 0 && s->perimeter()==0)
            //if (dynamic_cast<CompoundShape*>(s))
            {
                //CompoundShape
                while (temp.size() > 0)
                {
                    Shape *ss = temp[0];
                    s->addShape(ss);
                    temp.pop_front();
                }
                temp.push_front(s);
            }
            else
                temp.push_front(s);
        }
        while (temp.size()>0)
        {
            _result.push_back(temp[0]);
            temp.pop_front();
        }
    }

    std::deque<Shape *> getResult()
    {
        // return result.
        return _result;
    }

private:
    std::string _input;
    std::deque<Shape *> _result;
};

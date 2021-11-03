#ifndef ELLIPSE_H
#define ELLIPSE_H
#define _USE_MATH_DEFINES
#include <cmath>
#include <sstream>
#include <iomanip>
#include "shape.h"

class Ellipse : public Shape
{
public:
    Ellipse(){}
    
    Ellipse(std::string id, double semiMajorAxes, double semiMinorAxes)
    {
        if (IsEllipse(semiMajorAxes, semiMinorAxes))
        {
            _semiMajorAxes = semiMajorAxes;
            _semiMinorAxes = semiMinorAxes;
            _id = id;    
            _color = "white";
        }
        else
        {
            throw std::string("This is not an ellipse!");
        }
    }

    Ellipse(std::string id, double semiMajorAxes, double semiMinorAxes, std::string color)
    {
        if (IsEllipse(semiMajorAxes, semiMinorAxes))
        {
            _semiMajorAxes = semiMajorAxes;
            _semiMinorAxes = semiMinorAxes;
            _id = id;
            _color = color;
        }
        else
        {
            throw std::string("This is not an ellipse!");
        }
    }

    std::string id() { return _id; }

    std::string color() { return _color; }

    double area() const
    {
        // return the area of the Ellipse.
        return M_PI * _semiMajorAxes * _semiMinorAxes;
    }

    double perimeter() const
    {
        // return the perimeter of the Ellipse.
        return 2 * M_PI * _semiMinorAxes + 4 * (_semiMajorAxes - _semiMinorAxes);
    }

    std::string info() const
    {
        // return the info of the Ellipse.
        // ex. Ellipse (3.712, 4.000)
        std::stringstream ss;
        ss << std::fixed << std::setprecision(3);
        ss << "Ellipse (" << _semiMajorAxes << ", " << _semiMinorAxes << ")";
        return ss.str();
    }
    
private:
    double _semiMajorAxes, _semiMinorAxes;

    bool IsEllipse(double semiMajorAxes, double semiMinorAxes)
    {
        return (semiMajorAxes > 0 && semiMinorAxes > 0) && (semiMajorAxes >= semiMinorAxes);
    }
};
#endif
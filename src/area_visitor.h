#ifndef AREA_VISITOR_H
#define AREA_VISITOR_H
#include <cmath>
#include "visitor.h"
#include "ellipse.h"
#include "triangle.h"
#include "rectangle.h"
#include "compound_shape.h"

//class Ellipse;
//class Triangle;
//class Rectangle;
//class CompoundShape;

class AreaVisitor : public Visitor
{
public:
    void visit(Ellipse *ellipse)
    {
        // caculate the area of Ellipse.
        // DO NOT use ellipse->area() to get area directly.
        // you may add public function for Ellipse to get it's data members.
        _area = M_PI * ellipse->semiMajorAxes() * ellipse->semiMinorAxes();
    }

    void visit(Triangle *triangle)
    {
        // caculate the area of Triangle.
        // DO NOT use triangle->area() to get area directly.
        // you may add public function for Triangle to get it's data members.
        double s = (triangle->a() + triangle->b() + triangle->c()) / 2.0;
        _area = std::sqrt(s * (s - triangle->a()) * (s - triangle->b()) * (s - triangle->c()));
    }

    void visit(Rectangle *rectangle)
    {
        // caculate the area of Rectangle.
        // DO NOT use rectangle->area() to get area directly.
        // you may add public function for Rectangle to get it's data members.
        _area = rectangle->length() * rectangle->width();
    }

    void visit(CompoundShape *compoundShape)
    {
        // caculate the area of CompoundShape.
        // DO NOT use compoundShape->area() to get area directly.
        // you may add public function for CompoundShape to get it's data members.
        Iterator *it = compoundShape->createIterator();

        while (!it->isDone())
        {
            Shape *s = it->currentItem();
            Visitor *av = new AreaVisitor();
            s->accept(av);
            _area += ((AreaVisitor *)av)->area();
            delete av;
            it->next();
        }
    }

    double area() const
    {
        // return area;
        return _area;
    }

private:
    double _area;
};
#endif
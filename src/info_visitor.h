#ifndef INFO_VISITOR_H
#define INFO_VISITOR_H
#include <iostream>
#include <sstream>
#include "visitor.h"
#include "ellipse.h"
#include "triangle.h"
#include "rectangle.h"
#include "compound_shape.h"

class InfoVisitor : public Visitor
{
public:
    void visit(Ellipse *ellipse)
    {
        // create info of ellipse, same way as ellipse->info().
        // DO NOT use ellipse->info() to get info directly.
        // you may add public function for Ellipse to get it's data members.
        std::stringstream ss;
        ss << std::fixed << std::setprecision(3);
        ss << "Ellipse (" << ellipse->semiMajorAxes() << ", " << ellipse->semiMinorAxes() << ")";
        _info = ss.str();
        //std::cout << "aa" <<std::endl;
    }

    void visit(Triangle *triangle)
    {
        // create info of ellipse, same way as triangle->info().
        // DO NOT use triangle->info() to get info directly.
        // you may add public function for Triangle to get it's data members.
        std::stringstream ss;
        ss << std::fixed << std::setprecision(3);
        ss << "Triangle (";
        for (int i = 0; i < 3; i++)
        {
            ss << "[" << triangle->points()[i]->getX() << ", " << triangle->points()[i]->getY() << "]";
            if (i != 2)
                ss << ", ";
        }
        ss << ")";
        _info = ss.str();
    }

    void visit(Rectangle *rectangle)
    {
        // create info of rectangle, same way as rectangle->info().
        // DO NOT use rectangle->info() to get info directly.
        // you may add public function for Rectangle to get it's data members.
        std::stringstream ss;
        ss << std::fixed << std::setprecision(3);
        ss << "Rectangle (" << rectangle->length() << ", " << rectangle->width() << ")";
        _info = ss.str();
    }

    void visit(CompoundShape *compoundShape)
    {
        // create info of compoundShape, same way as compoundShape->info().
        // DO NOT use compoundShape->info() to get info directly.
        // you may add public function for CompoundShape to get it's data members.
        Iterator* it = compoundShape->createIterator();
        std::stringstream ss;
        ss << "Compound Shape {";
        while (!it->isDone())
        {
            Shape* s = it->currentItem();
            Visitor* iv = new InfoVisitor();
            s->accept(iv);
            ss << ((InfoVisitor*)iv)->info();
            if((it->currentItem()) != (compoundShape->shapes()).back())
                ss << ", ";
            delete iv;
            it->next();
        }
        ss << "}";
        _info = ss.str();
    }

    std::string info() const
    {
        // return info;
        return _info;
    }

private:
    std::string _info;
};
#endif
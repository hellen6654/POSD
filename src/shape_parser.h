#include <string>
#include <deque>
#include <iostream>
#include "two_dimensional_coordinate.h"
#include "triangle.h"
#include "ellipse.h"
#include "rectangle.h"
#include "compound_shape.h"
#include "shape.h"

class ShapeParser
{
public:
    ShapeParser(std::string input)
    {
        // initialize a scanner for handling input.
        // initialize a shape builder for handling building shape.
        s = new Scanner(input);
        b = new ShapeBuilder();
    }

    void parser()
    {
        // using Scanner::nextToken() to get all information to determine what to build,
        // and provide the argument the shape needed.
        // use functions in ShapeBuilder to build out the shape.
        // the shape with invalid argument should be ignored (see example bellow).
        std::deque<std::string> arg;
        std::string str = "";

        while (1)
        {
            try
            {
                str = s->nextToken();
                //std::cout << str << std::endl;
                if (str == "CompoundShape")
                {
                    b->buildCompoundShapeBegin();
                }
                else if (str == "}")
                {
                    b->buildCompoundShapeEnd();
                }
                else if (str != "{" && str != ",")
                {
                    std::string shapetype = str;
                    std::vector<double> coordinate;
                    std::string temp = "";
                    str = s->nextToken(); // should be a "("
                    while ((str = s->nextToken()) != ")")
                    {
                        if (str != ",")
                        {
                            coordinate.push_back(std::stod(str));
                        }     
                    }
                    try
                    {
                        if (shapetype == "Triangle" && coordinate.size()==6)
                        {
                            b->buildTriangle(coordinate[0], coordinate[1], coordinate[2], coordinate[3], coordinate[4], coordinate[5]);
                        }
                        else if (shapetype == "Rectangle"&& coordinate.size()==2)
                        {
                            b->buildRectangle(coordinate[0], coordinate[1]);
                        }
                        else if (shapetype == "Ellipse"&& coordinate.size()==2)
                        {
                            b->buildEllipse(coordinate[0], coordinate[1]);
                        }
                    }
                    catch (const std::string e)
                    {
                        //std::cout << e << std::endl;
                    }
                }
            }
            catch (const std::string &e)
            {
                break;
            }
        }
        _result = b->getResult();
    }

    std::deque<Shape *> getResult()
    {
        // return result.
        return _result;
    }

private:
    Scanner *s;
    ShapeBuilder *b;
    std::deque<Shape *> _result;
};

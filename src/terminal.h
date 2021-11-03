#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <regex>
#include <vector>
#include "rectangle.h"
#include "triangle.h"
#include "ellipse.h"
#include "sort.h"

class Terminal
{
public:
    Terminal(std::string input)
    {
        std::vector<std::string>::iterator it;
        std::vector<std::string> inputVec;
        std::vector<Shape *> shapes;
        std::string delimiter = ") ";
        std::string feature;
        std::string order;
        size_t pos = 0;
        while ((pos = input.find(delimiter)) != std::string::npos)
        {
            inputVec.push_back(input.substr(0, pos) + delimiter);
            input.erase(0, pos + delimiter.length());
        }
        pos = input.find(" ");
        feature = input.substr(0, pos);
        order = input.substr(pos + 1, input.back());
        if ((order != "inc" && order != "dec") ||
            (feature != "area" && feature != "perimeter") ||
            inputVec.size() == 0)
            throw std::string("invalid input");

        for (it = inputVec.begin(); it != inputVec.end(); it++)
        {
            Shape *temp = CheckShape(*it);
            if (temp != nullptr)
            {
                shapes.push_back(temp);
            }
        }
        if (shapes.size() == 0)
        {
            throw std::string("invalid input");
        }
        if (order == "inc")
        {
            quickSort(shapes.begin(), shapes.end(), AscendingCompare(feature));
        }
        else
        {
            quickSort(shapes.begin(), shapes.end(), DescendingCompare(feature));
        }
        MakeResult(shapes, feature);
    }

    std::string showResult()
    {
        return _result;
    }

private:
    std::string _input;
    std::string _result;
    const std::string _recNamePatten = "^Rectangle\\s+\\(.+\\)\\s*$"; // Rectangle (*)
    const std::string _ellNamePatten = "^Ellipse\\s+\\(.+\\)\\s*$";   // Ellipse(*)
    const std::string _triNamePatten = "^Triangle\\s+\\(.+\\)\\s*$";  //   Triangle(*)

    const std::string _coordinatePatten = "\\(((\\d+\\.?\\d*)|(\\d*\\.\\d+)),((\\d+\\.?\\d*)|(\\d*\\.\\d+))\\)$";                                                                                                                                                  // 整數 整數加小數 純小數
    const std::string _triCoordinatePatten = "\\(\\[-?((\\d+\\.?\\d*)|(\\d*\\.\\d+)),-?((\\d+\\.?\\d*)|(\\d*\\.\\d+))\\],\\[-?((\\d+\\.?\\d*)|(\\d*\\.\\d+)),-?((\\d+\\.?\\d*)|(\\d*\\.\\d+))\\],\\[-?((\\d+\\.?\\d*)|(\\d*\\.\\d+)),-?((\\d+\\.?\\d*)|(\\d*\\.\\d+))\\]\\)$"; //([,],[,],[,])

    Shape *CheckShape(std::string line)
    {
        std::regex rectName(_recNamePatten);
        std::regex ellName(_ellNamePatten);
        std::regex triName(_triNamePatten);
        //check name part
        if (std::regex_match(line, rectName) || std::regex_match(line, ellName) || std::regex_match(line, triName))
        {
            std::regex coordinate(_coordinatePatten);
            std::regex triCoordinate(_triCoordinatePatten);
            size_t pos = 0;
            std::vector<std::string> shape;
            //erase space
            while ((pos = line.find(" ")) != std::string::npos)
                line.erase(pos, 1);
            shape.push_back(line.substr(0, line.find("("))); //get shape name
            line.erase(0, line.find("("));                   //erase shape name
            if (std::regex_match(line, coordinate))
            {
                //rectangle & ellipse
                line.erase(line.find("("), 1).erase(line.find(")"), 1);
                shape.push_back(line.substr(0, line.find(",")));
                shape.push_back(line.substr(line.find(",") + 1, line.back()));
                return MakeShape(shape.begin());
            }
            else if (std::regex_match(line, triCoordinate))
            {
                //triangle
                line.erase(line.find("("), 1).erase(line.find(")"), 1);
                while ((pos = line.find("[")) != std::string::npos)
                    line.erase(pos, 1);
                while ((pos = line.find("]")) != std::string::npos)
                    line.erase(pos, 1);
                while ((pos = line.find(",")) != std::string::npos)
                {
                    shape.push_back(line.substr(0, pos));
                    line.erase(0, pos + 1);
                }
                shape.push_back(line);
                return MakeShape(shape.begin());
            }
            else
            {
                return nullptr;
            }
        }
        else
        {
            return nullptr;
        }
    }

    Shape *MakeShape(std::vector<std::string>::iterator begin)
    {
        try
        {
            if (*begin == "Rectangle")
            {
                double x = std::stod(*(begin + 1));
                double y = std::stod(*(begin + 2));
                return new Rectangle("0",x, y);
            }
            else if (*begin == "Ellipse")
            {
                double x = std::stod(*(begin + 1));
                double y = std::stod(*(begin + 2));
                return new Ellipse("0",x, y);
            }
            else if (*begin == "Triangle")
            {
                std::vector<TwoDimensionalCoordinate *> points;
                for (int i = 1; i < 7; i += 2)
                {
                    double x = std::stod(*(begin + i));
                    double y = std::stod(*(begin + i + 1));
                    points.push_back(new TwoDimensionalCoordinate(x, y));
                }
                return new Triangle("0",points);
            }
            else
            {
                return nullptr;
            }
        }
        catch (const std::string e)
        {
            return nullptr;
        }
    }

    void MakeResult(std::vector<Shape *> shapes, std::string feature)
    {
        std::stringstream ss;
        std::string temp = "";
        std::vector<Shape *>::iterator it;
        ss << std::fixed << std::setprecision(3);
        if (feature == "area")
        {
            for (it=shapes.begin() ;it!=shapes.end();it++)
            {
                ss << (*it)->area();
                temp += ss.str();
                if (*it != shapes.back())
                    temp += "\n";

                ss.str("");
                ss.clear();
            }
        }
        else
        {
            for (it=shapes.begin() ;it!=shapes.end();it++)
            {
                ss << (*it)->perimeter();
                temp += ss.str();
                if (*it != shapes.back())
                    temp += "\n";

                ss.str("");
                ss.clear();
            }
        }
        _result = temp;
    }
};

#ifndef TWO_DIMENSIONAL_COORDINATE_H
#define TWO_DIMENSIONAL_COORDINATE_H
class TwoDimensionalCoordinate
{
public:
    TwoDimensionalCoordinate(double x, double y) : _x(x), _y(y) {}

    double getX()
    {
        // return x;
        return _x;
    }

    double getY()
    {
        // return y;
        return _y;
    }

    double Distance(TwoDimensionalCoordinate * point)
    {   
        return std::sqrt(std::pow(point->getX()-_x,2)+std::pow(point->getY()-_y,2));
    }
private:
    double _x, _y;
};
#endif
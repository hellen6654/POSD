#include "../src/triangle.h"

//直角三角形 7 24 25
TEST(TRIANGLE,CreateRightTriangle)
{
    std::vector<TwoDimensionalCoordinate*> points
    {
        new TwoDimensionalCoordinate(0,0),
        new TwoDimensionalCoordinate(7,0),
        new TwoDimensionalCoordinate(0,24)
    };

    Triangle triangle(points);
    ASSERT_NEAR(84,triangle.area(),0.001);
    ASSERT_NEAR(56,triangle.perimeter(),0.001);
    ASSERT_EQ("Triangle ([0.000, 0.000], [7.000, 0.000], [0.000, 24.000])",
            triangle.info());
}

//等腰三角形 16 17 17
TEST(TRIANGLE,CreateIsoscelesTriangle)
{
    std::vector<TwoDimensionalCoordinate*> points;
    TwoDimensionalCoordinate pointA(-15,-1.4);
    TwoDimensionalCoordinate pointB(0,6.6);
    TwoDimensionalCoordinate pointC(0,-9.4);

    points.push_back(&pointA);
    points.push_back(&pointB);
    points.push_back(&pointC);

    Triangle triangle(points);
    ASSERT_NEAR(120,triangle.area(),0.001);
    ASSERT_NEAR(50,triangle.perimeter(),0.001);
    ASSERT_EQ("Triangle ([-15.000, -1.400], [0.000, 6.600], [0.000, -9.400])",
            triangle.info());
}

//任意三角形 5 8.5 10.5
TEST(TRIANGLE,CreateAnyTriangle)
{
    std::vector<TwoDimensionalCoordinate*> points;
    TwoDimensionalCoordinate pointA(-3.0,0.0);
    TwoDimensionalCoordinate pointB(7.5,0);
    TwoDimensionalCoordinate pointC(0,4);

    points.push_back(&pointA);
    points.push_back(&pointB);
    points.push_back(&pointC);

    Triangle triangle(points);
    ASSERT_NEAR(21,triangle.area(),0.001);
    ASSERT_NEAR(24,triangle.perimeter(),0.001);
    ASSERT_EQ("Triangle ([-3.000, 0.000], [7.500, 0.000], [0.000, 4.000])",
            triangle.info());
}

//不是三角形
TEST(TRIANGLE,CreateErrorTriangle)
{
    std::vector<TwoDimensionalCoordinate*> points;
    TwoDimensionalCoordinate pointA(0.0,0.0);
    TwoDimensionalCoordinate pointB(2.0,2.0);
    TwoDimensionalCoordinate pointC(-2.0,-2.0);

    points.push_back(&pointA);
    points.push_back(&pointB);
    points.push_back(&pointC);
    try
    {
        Triangle triangle(points);
    }
    catch(std::string e)
    {
        ASSERT_EQ("This is not a triangle!",e);
    }
}

//Vector 數量不正確
TEST(TRIANGLE,CreateErrorTriangle2)
{
    std::vector<TwoDimensionalCoordinate*> points;
    TwoDimensionalCoordinate pointA(0.0,0.0);
    TwoDimensionalCoordinate pointB(2.0,2.0);
    
    points.push_back(&pointA);
    points.push_back(&pointB);

    try
    {
        Triangle triangle(points);
    }
    catch(std::string e)
    {
        ASSERT_EQ("This is not a triangle!",e);
    }
}
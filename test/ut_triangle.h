#include "../src/triangle.h"

TEST(TRIANGLE, CreateRightTriangleWithId)
{
    std::vector<TwoDimensionalCoordinate *> points{
        new TwoDimensionalCoordinate(0, 0),
        new TwoDimensionalCoordinate(7, 0),
        new TwoDimensionalCoordinate(0, 24)};

    Triangle triangle("0", points);
    ASSERT_EQ("0",triangle.id());
}

TEST(TRIANGLE, CreateRightTriangleWithIdAndColor)
{
    std::vector<TwoDimensionalCoordinate *> points{
        new TwoDimensionalCoordinate(0, 0),
        new TwoDimensionalCoordinate(7, 0),
        new TwoDimensionalCoordinate(0, 24)};

    Triangle triangle("0", points,"black");
    ASSERT_EQ("0",triangle.id());
    ASSERT_EQ("black",triangle.color());
}

//直角三角形 7 24 25
TEST(TRIANGLE, CreateRightTriangle)
{
    std::vector<TwoDimensionalCoordinate *> points{
        new TwoDimensionalCoordinate(0, 0),
        new TwoDimensionalCoordinate(7, 0),
        new TwoDimensionalCoordinate(0, 24)};

    Triangle triangle("0", points);
    ASSERT_NEAR(84.000, triangle.area(), 0.001);
    ASSERT_NEAR(56.000, triangle.perimeter(), 0.001);
    ASSERT_EQ("Triangle ([0.000, 0.000], [7.000, 0.000], [0.000, 24.000])",
              triangle.info());
}

//等腰三角形 16 17 17
TEST(TRIANGLE, CreateIsoscelesTriangle)
{
    std::vector<TwoDimensionalCoordinate *> points{
        new TwoDimensionalCoordinate(-15, -1.4),
        new TwoDimensionalCoordinate(0, 6.6),
        new TwoDimensionalCoordinate(0, -9.4)};
    Triangle triangle("0", points);
    ASSERT_NEAR(120, triangle.area(), 0.001);
    ASSERT_NEAR(50, triangle.perimeter(), 0.001);
    ASSERT_EQ("Triangle ([-15.000, -1.400], [0.000, 6.600], [0.000, -9.400])",
              triangle.info());
}

//任意三角形 5 8.5 10.5
TEST(TRIANGLE, CreateAnyTriangle)
{
    std::vector<TwoDimensionalCoordinate *> points{
        new TwoDimensionalCoordinate(-3.0, 0.0),
        new TwoDimensionalCoordinate(7.5, 0),
        new TwoDimensionalCoordinate(0, 4)};
    Triangle triangle("0", points);
    ASSERT_NEAR(21, triangle.area(), 0.001);
    ASSERT_NEAR(24, triangle.perimeter(), 0.001);
    ASSERT_EQ("Triangle ([-3.000, 0.000], [7.500, 0.000], [0.000, 4.000])",
              triangle.info());
}

//不是三角形
TEST(TRIANGLE, CreateErrorTriangle)
{
    std::vector<TwoDimensionalCoordinate *> points{
        new TwoDimensionalCoordinate(0.0, 0.0),
        new TwoDimensionalCoordinate(2.0, 2.0),
        new TwoDimensionalCoordinate(-2.0, -2.0)};
    try
    {
        Triangle triangle("0", points);
    }
    catch (std::string e)
    {
        ASSERT_EQ("This is not a triangle!", e);
    }
}

//Vector 數量不正確
TEST(TRIANGLE, CreateErrorTriangle2)
{
    std::vector<TwoDimensionalCoordinate *> points{
        new TwoDimensionalCoordinate(0.0, 0.0),
        new TwoDimensionalCoordinate(2.0, 2.0)};

    try
    {
        Triangle triangle("0", points);
    }
    catch (std::string e)
    {
        ASSERT_EQ("This is not a triangle!", e);
    }
}

TEST(TRIANGLE, TriangleAddShape)
{
    std::vector<TwoDimensionalCoordinate *> points{
        new TwoDimensionalCoordinate(0.0, 0.0),
        new TwoDimensionalCoordinate(2.0, 2.0),
        new TwoDimensionalCoordinate(-2.0, 2.0)};

    try
    {
        Shape* triangle = new Triangle("0", points);
        Shape* triangle2 = new Triangle("1", points);
        triangle->addShape(triangle2);
    }
    catch (std::string e)
    {
        ASSERT_EQ("Only compound shape can add shape!", e);
    }
}

TEST(TRIANGLE, TriangleDeleteShape)
{
    std::vector<TwoDimensionalCoordinate *> points{
        new TwoDimensionalCoordinate(0.0, 0.0),
        new TwoDimensionalCoordinate(2.0, 2.0),
        new TwoDimensionalCoordinate(-2.0, 2.0)};

    try
    {
        Shape* triangle = new Triangle("0", points);
        Shape* triangle2 = new Triangle("1", points);
        triangle->deleteShapeById("1");
    }
    catch (std::string e)
    {
        ASSERT_EQ("Only compound shape can delete shape!", e);
    }
}

TEST(TRIANGLE, TriangleGetShapeById)
{
    std::vector<TwoDimensionalCoordinate *> points{
        new TwoDimensionalCoordinate(0.0, 0.0),
        new TwoDimensionalCoordinate(2.0, 2.0),
        new TwoDimensionalCoordinate(-2.0, 2.0)};

    try
    {
        Shape* triangle = new Triangle("0", points);
        Shape* triangle2 = new Triangle("1", points);
        triangle->getShapeById("0");
    }
    catch (std::string e)
    {
        ASSERT_EQ("Only compound shape can get shape!", e);
    }
}
#include "../src/rectangle.h"

TEST(RECTANGLE,CreateRectangleWithID)
{
    Rectangle rectangle("0",2.2,5.7);
    ASSERT_NEAR((2.2+5.7)*2,rectangle.perimeter(),0.001);
    ASSERT_NEAR(2.2*5.7,rectangle.area(),0.001);
    ASSERT_EQ("0",rectangle.id());
    ASSERT_EQ("white",rectangle.color());
    ASSERT_EQ("Rectangle (2.200, 5.700)",rectangle.info());
}

TEST(RECTANGLE,CreateRectangleWithIDAndColor)
{
    Rectangle rectangle("0",2.2,5.7,"black");
    ASSERT_NEAR((2.2+5.7)*2,rectangle.perimeter(),0.001);
    ASSERT_NEAR(2.2*5.7,rectangle.area(),0.001);
    ASSERT_EQ("0",rectangle.id());
    ASSERT_EQ("black",rectangle.color());
    ASSERT_EQ("Rectangle (2.200, 5.700)",rectangle.info());
}

TEST(RECTANGLE,CreateRectangle)
{
    Rectangle rectangle("0",2.2,5.7);
    ASSERT_NEAR((2.2+5.7)*2,rectangle.perimeter(),0.001);
    ASSERT_NEAR(2.2*5.7,rectangle.area(),0.001);
    ASSERT_EQ("Rectangle (2.200, 5.700)",rectangle.info());
}

TEST(RECTANGLE,CreateErrorRectangle)
{
    try
    {
        Rectangle rectangle("0",0,5);
    }
    catch(std::string e)
    {
        ASSERT_EQ("This is not a rectangle!",e);
    }
}

TEST(RECTANGLE,RectangleAddShape)
{
    try
    {
        Shape* rectangle  = new Rectangle("0",5,5);
        Shape* rectangle2 = new Rectangle("1",5,5);
        rectangle->addShape(rectangle2);
    }
    catch(std::string e)
    {
        ASSERT_EQ("Only compound shape can add shape!",e);
    }
}

TEST(RECTANGLE,RectangleDeleteShape)
{
    try
    {
        Shape* rectangle  = new Rectangle("0",5,5);
        Shape* rectangle2 = new Rectangle("1",5,5);
        rectangle->deleteShapeById("1");
    }
    catch(std::string e)
    {
        ASSERT_EQ("Only compound shape can delete shape!",e);
    }
}

TEST(RECTANGLE,RectangleGetShapeById)
{
    try
    {
        Shape* rectangle  = new Rectangle("0",5,5);
        Shape* rectangle2 = new Rectangle("1",5,5);
        rectangle->getShapeById("1");
    }
    catch(std::string e)
    {
        ASSERT_EQ("Only compound shape can get shape!",e);
    }
}
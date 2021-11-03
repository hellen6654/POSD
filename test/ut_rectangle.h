#include "../src/rectangle.h"

TEST(Rectangle,CreateRectangle)
{
    Rectangle rectangle(2.2,5.7);
    ASSERT_NEAR((2.2+5.7)*2,rectangle.perimeter(),0.001);
    ASSERT_NEAR(2.2*5.7,rectangle.area(),0.001);
    ASSERT_EQ("Rectangle (2.200, 5.700)",rectangle.info());
}

TEST(Rectangle,CreateErrorRectangle)
{
    //ASSERT_THROW(),std::string);
    try
    {
        Rectangle rectangle(0,5);
    }
    catch(std::string e)
    {
        ASSERT_EQ("This is not a rectangle!",e);
    }
}
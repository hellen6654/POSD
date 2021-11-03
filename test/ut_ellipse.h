#include "../src/ellipse.h"

TEST(ELLIPSE,CreateEllipse)
{
    Ellipse ellipse(1.2,0.5);
    ASSERT_NEAR(M_PI*1.2*0.5,ellipse.area(),0.001);
    ASSERT_NEAR(2*M_PI*0.5+4*(1.2-0.5),ellipse.perimeter(),0.001);
    ASSERT_EQ("Ellipse (1.200, 0.500)",ellipse.info());
}

TEST(ELLIPSE,CreateEllipse2)
{
    Ellipse ellipse(1.5,1.5);
    ASSERT_NEAR(M_PI*1.5*1.5,ellipse.area(),0.001);
    ASSERT_NEAR(2*M_PI*1.5+4*(1.5-1.5),ellipse.perimeter(),0.001);
    ASSERT_EQ("Ellipse (1.500, 1.500)",ellipse.info());
}

TEST(ELLIPSE,CreateErrorEllipse)
{
    try
    {
        Ellipse ellipse(0,4);
    }
    catch(std::string e)
    {
        ASSERT_EQ("This is not a ellipse!",e);
    }
}

TEST(ELLIPSE,CreateErrorEllipse2)
{
    try
    {
        Ellipse ellipse(3,4);
    }
    catch(std::string e)
    {
        ASSERT_EQ("This is not a ellipse!",e);
    }
}
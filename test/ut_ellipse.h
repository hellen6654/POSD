#include "../src/ellipse.h"


TEST(ELLIPSE,CreateEllipseWithID)
{
    Ellipse ellipse("123",1.2,0.5);
    ASSERT_NEAR(M_PI*1.2*0.5,ellipse.area(),0.001);
    ASSERT_NEAR(2*M_PI*0.5+4*(1.2-0.5),ellipse.perimeter(),0.001);
    ASSERT_EQ("Ellipse (1.200, 0.500)",ellipse.info());
    ASSERT_EQ("123",ellipse.id());
}

TEST(ELLIPSE,CreateEllipseWithIDAndColor)
{
    Ellipse ellipse("0",1.2,0.5,"black");
    ASSERT_NEAR(M_PI*1.2*0.5,ellipse.area(),0.001);
    ASSERT_NEAR(2*M_PI*0.5+4*(1.2-0.5),ellipse.perimeter(),0.001);
    ASSERT_EQ("Ellipse (1.200, 0.500)",ellipse.info());
    ASSERT_EQ("0",ellipse.id());
    ASSERT_EQ("black",ellipse.color());
}

TEST(ELLIPSE,CreateEllipse)
{
    Ellipse ellipse("0",1.2,0.5);
    ASSERT_NEAR(M_PI*1.2*0.5,ellipse.area(),0.001);
    ASSERT_NEAR(2*M_PI*0.5+4*(1.2-0.5),ellipse.perimeter(),0.001);
    ASSERT_EQ("Ellipse (1.200, 0.500)",ellipse.info());
}

TEST(ELLIPSE,CreateEllipse2)
{
    Ellipse ellipse("0",1.5,1.5);
    ASSERT_NEAR(M_PI*1.5*1.5,ellipse.area(),0.001);
    ASSERT_NEAR(2*M_PI*1.5+4*(1.5-1.5),ellipse.perimeter(),0.001);
    ASSERT_EQ("Ellipse (1.500, 1.500)",ellipse.info());
}

TEST(ELLIPSE,CreateErrorEllipse)
{
    try
    {
        Ellipse ellipse("0",0,4);
    }
    catch(std::string e)
    {
        ASSERT_EQ("This is not an ellipse!",e);
    }
}

TEST(ELLIPSE,CreateErrorEllipse2)
{
    try
    {
        Ellipse ellipse("0",3,4);
    }
    catch(std::string e)
    {
        ASSERT_EQ("This is not an ellipse!",e);
    }
}

TEST(ELLIPSE,EllipseAddShape)
{
    try
    {
        Shape *ellipse = new Ellipse("0",4,3);
        Shape *ellipse2 = new Ellipse("0",4,3);
        ellipse->addShape(ellipse2);
    }
    catch(std::string e)
    {
        ASSERT_EQ("Only compound shape can add shape!",e);
    }
}

TEST(ELLIPSE,EllipseDeleteShape)
{
    try
    {
        Shape *ellipse = new Ellipse("0",4,3);
        Shape *ellipse2 = new Ellipse("1",4,3);
        ellipse->deleteShapeById("1");
    }
    catch(std::string e)
    {
        ASSERT_EQ("Only compound shape can delete shape!",e);
    }
}

TEST(ELLIPSE,EllipseGetShapeById)
{
    try
    {
        Shape *ellipse = new Ellipse("0",4,3);
        Shape *ellipse2 = new Ellipse("1",4,3);
        ellipse->getShapeById("1");
    }
    catch(std::string e)
    {
        ASSERT_EQ("Only compound shape can get shape!",e);
    }
}
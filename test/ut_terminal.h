#include "../src/terminal.h"

TEST(TERMINAL, ValidInputToTerminal)
{
    Terminal terminal("Rectangle (2,2) Triangle ([0,0],[-3,0],[0,4]) area inc");
    ASSERT_EQ("4.000\n6.000", terminal.showResult());
}

TEST(TERMINAL, ValidInputToTerminal_2)
{
    Terminal terminal("Ellipse (4, 3) Rectangle (1, 1) Triangle ([0,0],[3,0],[0,4]) area inc");
    ASSERT_EQ("1.000\n6.000\n37.699", terminal.showResult());
}

TEST(TERMINAL, AreaInc)
{
    Terminal terminal("Ellipse (4, 3) Rectangle (1, 2) Rectangle (2, 2) Triangle ([0,0],[3,0],[0,4]) area inc");
    ASSERT_EQ("2.000\n4.000\n6.000\n37.699", terminal.showResult());
}

TEST(TERMINAL, AreaDec_2)
{
    Terminal terminal("Ellipse (2, 1) Ellipse (3, 2) Ellipse (4, 3) area dec");
    ASSERT_EQ("37.699\n18.850\n6.283", terminal.showResult());
}

TEST(TERMINAL, AreaInc_3)
{
    Terminal terminal("Rectangle (1, 2) Rectangle (2, 2) Rectangle (3, 2) area inc");
    ASSERT_EQ("2.000\n4.000\n6.000", terminal.showResult());
}

TEST(TERMINAL, AreaInc_4)
{
    Terminal terminal("Rectangle (2,3) Ellipse (2, 2) Ellipse (3, 2) area inc");
    ASSERT_EQ("6.000\n12.566\n18.850", terminal.showResult());
}

TEST(TERMINAL, AreaDec)
{
    Terminal terminal("Ellipse (4, 3) Rectangle (2, 2) Triangle ([0,0],[3,0],[0,4]) area dec");
    ASSERT_EQ("37.699\n6.000\n4.000", terminal.showResult());
}

TEST(TERMINAL, PerimeterInc)
{
    Terminal terminal("Ellipse (4, 3) Rectangle (2, 2) Triangle ([0,0],[3,0],[0,4]) perimeter inc");
    ASSERT_EQ("8.000\n12.000\n22.850", terminal.showResult());
}

TEST(TERMINAL, PerimeterDec)
{
    Terminal terminal("Ellipse (4, 3) Rectangle (2, 2) Triangle ([0,0],[3,0],[0,4]) perimeter dec");
    ASSERT_EQ("22.850\n12.000\n8.000", terminal.showResult());
}

TEST(TERMINAL, InvalidInputToTerminal)
{
    try
    {
        Terminal terminal("Rectangle (3.7, 4.2) Ellipse (4, 4) area");
    }
    catch (std::string e)
    {
        ASSERT_EQ("invalid input", e);
    }
}

TEST(TERMINAL, InvalidInputToTerminal_2)
{
    try
    {
        Terminal terminal("area inc");
    }
    catch (std::string e)
    {
        ASSERT_EQ("invalid input", e);
    }
}

TEST(TERMINAL, InvalidInputToTerminal_3)
{
    try
    {
        Terminal terminal("Rectangle (3.7, 4.2) Ellipse (%3, 4) area inc");
    }
    catch (std::string e)
    {
        ASSERT_EQ("This is not an ellipse!", e);
    }
}

TEST(TERMINAL, ValidInputToTerminaLowCap)
{
    Terminal terminal("Rectangle (2, 2) triangle ([0,0],[3,0],[0,4]) area inc");
    ASSERT_EQ("4.000",terminal.showResult());
}

TEST(TERMINAL, ValidInputToTerminaIgnoreWrongArgment)
{
    Terminal terminal("Rectangle (2, 2) Rectangle (1, 1) Ellipse(2#$, 1) area inc");
    ASSERT_EQ("1.000\n4.000", terminal.showResult());
}

TEST(TERMINAL, ValidInputToTerminaIgnoreWrongShapeName)
{
    Terminal terminal("Rectangle (2, 2) Rectangle (1, 1) Ellipse$%^&(1, 1) area inc");
    ASSERT_EQ("1.000\n4.000", terminal.showResult());
}

TEST(TERMINAL, ValidInputToTerminaAllShapeInvalid)
{
    try 
    {
      Terminal("Rectangle (0, 0) Ellipse (-1, -1) area inc");
    }
    catch(std::string e) 
    {
      ASSERT_EQ("invalid input", e);
    }
}

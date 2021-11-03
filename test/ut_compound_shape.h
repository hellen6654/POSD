#include <string>
#include "../src/rectangle.h"
#include "../src/triangle.h"
#include "../src/ellipse.h"
#include "../src/compound_shape.h"

class CompoundShapeTest : public testing::Test
{
protected:
    void SetUp() override
    {
        std::vector<TwoDimensionalCoordinate *> pointsA{
            new TwoDimensionalCoordinate(0, 0),
            new TwoDimensionalCoordinate(7, 0),
            new TwoDimensionalCoordinate(0, 24)};
        std::vector<TwoDimensionalCoordinate *> pointsB{
            new TwoDimensionalCoordinate(0, 0),
            new TwoDimensionalCoordinate(14, 0),
            new TwoDimensionalCoordinate(7, 24)};

        t72425 = new Triangle("0", pointsA);
        /* perimeter = 56 / area = 84  */

        t142525 = new Triangle("1", pointsB);
        /* perimeter = 64 / area = 168  */

        r71 = new Rectangle("2", 7, 1);
        /* perimeter = 16 / area = 7  */

        r63 = new Rectangle("3", 6, 3);
        /* perimeter = 18 / area = 18  */

        e87 = new Ellipse("4", 8, 7);
        /* perimeter = 47.982 / area = 175.929 */

        r22 = new Rectangle("5", 2, 2);
        /* perimeter = 8 / area = 4 */

        r34 = new Rectangle("6", 3, 4);
        /* perimeter = 14 / area = 12 */

        shapes.push_back(t72425);
        shapes.push_back(r71);
        shapes.push_back(e87);

        shapes2.push_back(t142525);
        shapes2.push_back(r63);

        shapes3.push_back(r22);
        shapes3.push_back(r34);
    }

    void TearDown() override
    {
        delete t72425;
        delete t142525;
        delete r71;
        delete r63;
        delete e87;
    }
    Shape *t72425;
    Shape *t142525;
    Shape *r71;
    Shape *r63;
    Shape *e87;
    Shape *r22;
    Shape *r34;
    std::vector<Shape *> shapes;
    /* perimeter = 119.982 / area = 266.929 */
    std::vector<Shape *> shapes2;
    /* perimeter = 82 / area =  186 */
    std::vector<Shape *> shapes3;
    /* perimeter = 8 / area =  4 */
    std::vector<Shape *> emptyShapes;
};

TEST_F(CompoundShapeTest, CreateEmptyCompoundShape)
{
    try
    {
        CompoundShape compoundShape("0", &emptyShapes);
    }
    catch (const std::string e)
    {
        ASSERT_EQ("This is not a compound shape!", e);
    }
}

TEST_F(CompoundShapeTest, CreateOneCompoundShape)
{
    CompoundShape compoundShape("0", &shapes);
    ASSERT_NEAR(t72425->area() + r71->area() + e87->area(), compoundShape.area(), 0.001);
    ASSERT_NEAR(t72425->perimeter() + r71->perimeter() + e87->perimeter(), compoundShape.perimeter(), 0.001);
    std::string infoStr = std::string("Compound Shape {") + t72425->info() + ", " + r71->info() + ", " + e87->info() + "}";
    ASSERT_EQ(infoStr, compoundShape.info());
}

TEST_F(CompoundShapeTest, AddShapeToCompoundShape)
{
    CompoundShape compoundShape("0", &shapes);
    compoundShape.addShape(t142525);
    ASSERT_NEAR(t72425->area() + r71->area() + e87->area() + t142525->area(), compoundShape.area(), 0.001);
    ASSERT_NEAR(t72425->perimeter() + r71->perimeter() + e87->perimeter() + t142525->perimeter(), compoundShape.perimeter(), 0.001);
    std::string infoStr = std::string("Compound Shape {") + t72425->info() + ", " + r71->info() + ", " + e87->info() + ", " + t142525->info() + "}";
    ASSERT_EQ(infoStr, compoundShape.info());
}

TEST_F(CompoundShapeTest, AddCompoundShapeToCompoundShape)
{
    CompoundShape compoundShape("8", &shapes);
    compoundShape.addShape(new CompoundShape("9", &shapes2));
    ASSERT_NEAR(t72425->area() + r71->area() + e87->area() + t142525->area() + r63->area(), compoundShape.area(), 0.001);
    ASSERT_NEAR(t72425->perimeter() + r71->perimeter() + e87->perimeter() + t142525->perimeter() + r63->perimeter(), compoundShape.perimeter(), 0.001);
    std::string infoStr = std::string("Compound Shape {") + t72425->info() + ", " + r71->info() + ", " + e87->info() + ", Compound Shape {" + t142525->info() + ", " + r63->info() + "}}";
    ASSERT_EQ(infoStr, compoundShape.info());
}

TEST_F(CompoundShapeTest, DeleteShapeFromCompoundShape)
{
    CompoundShape compoundShape("888", &shapes2);
    compoundShape.deleteShapeById("3");
    ASSERT_NEAR(t142525->area(), compoundShape.area(), 0.001);
    ASSERT_NEAR(t142525->perimeter(), compoundShape.perimeter(), 0.001);
    std::string infoStr = std::string("Compound Shape {") + t142525->info() + "}";
    ASSERT_EQ(infoStr, compoundShape.info());
}

TEST_F(CompoundShapeTest, DeleteShapeFromCompoundShapeError)
{
    CompoundShape compoundShape("888", &shapes);
    try
    {
        compoundShape.deleteShapeById("123");
    }
    catch (const std::string e)
    {
        ASSERT_EQ("Expected delete shape but shape not found", e);
    }
}

TEST_F(CompoundShapeTest, GetShapeFromCompoundShape)
{
    CompoundShape compoundShape("888", &shapes);
    Shape *shape = compoundShape.getShapeById("0");
    ASSERT_NEAR(t72425->area(), shape->area(), 0.001);
    ASSERT_NEAR(t72425->perimeter(), shape->perimeter(), 0.001);
    ASSERT_EQ(t72425->info(), shape->info());
}

TEST_F(CompoundShapeTest, GetShapeFromCompoundShapeError)
{
    CompoundShape compoundShape("888", &shapes);
    try
    {
        Shape *shape = compoundShape.getShapeById("123");
    }
    catch (const std::string e)
    {
        ASSERT_EQ("Expected get shape but shape not found", e);
    }
}

TEST_F(CompoundShapeTest, DeleteShapeFromSubSubCompoundShape)
{
    CompoundShape compoundShape("7", &shapes);
    CompoundShape compoundShape2("8", &shapes2);
    CompoundShape compoundShape3("9", &shapes3);
    compoundShape2.addShape(&compoundShape3);
    compoundShape.addShape(&compoundShape2);

    compoundShape.deleteShapeById("3");

    ASSERT_NEAR(t72425->area() + r71->area() + e87->area() + t142525->area() + r22->area()+r34->area(), compoundShape.area(), 0.001);
    ASSERT_NEAR(t72425->perimeter() + r71->perimeter() + e87->perimeter() + t142525->perimeter()  + r22->perimeter()+r34->perimeter(), compoundShape.perimeter(), 0.001);
    std::string infoStr = std::string("Compound Shape {") + t72425->info() + ", " + r71->info() + ", " + e87->info() + ", Compound Shape {" + t142525->info()  + ", Compound Shape {" + r22->info() +", "+r34->info() +"}}}";
    ASSERT_EQ(infoStr, compoundShape.info());
}

TEST_F(CompoundShapeTest, GetShapeFromSubCompoundShape)
{
    CompoundShape compoundShape("8", &shapes);
    compoundShape.addShape(new CompoundShape("9", &shapes2));
    Shape *shape = compoundShape.getShapeById("3");
    ASSERT_NEAR(r63->area(), shape->area(), 0.001);
    ASSERT_NEAR(r63->perimeter(), shape->perimeter(), 0.001);
    ASSERT_EQ(r63->info(), shape->info());
}

TEST_F(CompoundShapeTest, GetShapeFromSubCompoundShapeError)
{
    try
    {
        CompoundShape compoundShape("8", &shapes);
        compoundShape.addShape(new CompoundShape("9", &shapes2));
        Shape *shape = compoundShape.getShapeById("5");
    }
    catch (const std::string e)
    {
        ASSERT_EQ("Expected get shape but shape not found",e);
    }
}
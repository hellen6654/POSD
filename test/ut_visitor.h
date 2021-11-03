#include "../src/area_visitor.h"
#include "../src/info_visitor.h"

class VisitorTest : public testing::Test
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

        t72425 = new Triangle("0", pointsA,"red");
        /* perimeter = 56 / area = 84  */

        t142525 = new Triangle("1", pointsB,"orange");
        /* perimeter = 64 / area = 168  */

        r71 = new Rectangle("2", 7, 1,"yellow");
        /* perimeter = 16 / area = 7  */

        r63 = new Rectangle("3", 6, 3,"green");
        /* perimeter = 18 / area = 18  */

        e87 = new Ellipse("4", 8, 7,"blue");
        /* perimeter = 47.982 / area = 175.929 */

        r22 = new Rectangle("5", 2, 2,"indigo");
        /* perimeter = 8 / area = 4 */

        r34 = new Rectangle("6", 3, 4,"violet");
        /* perimeter = 14 / area = 12 */

        shapes.push_back(t72425);

        shapes2.push_back(t142525);
        shapes2.push_back(r63);

        shapes3.push_back(r22);
        shapes3.push_back(r34);
        cs = new CompoundShape("9999", shapes);
        cs2 = new CompoundShape("1234", shapes3);
        cs->addShape(cs2);
        cs->addShape(r71);
    }

    void TearDown() override
    {
        delete t72425;
        delete t142525;
        delete r71;
        delete r63;
        delete e87;
        delete r22;
        delete r34;
        delete cs;
        delete cs2;
    }
    Shape *t72425;
    Shape *t142525;
    Shape *r71;

    Shape *r63;
    Shape *e87;

    Shape *r22;
    Shape *r34;
    std::list<Shape *> shapes;
    /* perimeter = 119.982 / area = 266.929 */
    std::list<Shape *> shapes2;
    /* perimeter = 82 / area =  186 */
    std::list<Shape *> shapes3;
    /* perimeter = 8 / area =  4 */
    std::list<Shape *> emptyShapes;
    CompoundShape *cs;
    CompoundShape *cs2;
    Visitor *v;
};

TEST_F(VisitorTest,visitEllipse)
{
    v = new AreaVisitor();
    e87->accept(v);
    ASSERT_DOUBLE_EQ(e87->area(),((AreaVisitor*)v)->area());
    delete v;
    v = new InfoVisitor();
    e87->accept(v);
    ASSERT_EQ(e87->info(),((InfoVisitor*)v)->info());
    delete v;
}

TEST_F(VisitorTest,visitTriangle)
{
    v = new AreaVisitor();
    t72425->accept(v);
    ASSERT_DOUBLE_EQ(t72425->area(),((AreaVisitor*)v)->area());
    delete v;
    v = new InfoVisitor();
    t72425->accept(v);
    ASSERT_EQ(t72425->info(),((InfoVisitor*)v)->info());
    delete v;
}

TEST_F(VisitorTest,visitRectangle)
{
    v = new AreaVisitor();
    r34->accept(v);
    ASSERT_DOUBLE_EQ(r34->area(),((AreaVisitor*)v)->area());
    delete v;
    v = new InfoVisitor();
    r34->accept(v);
    ASSERT_EQ(r34->info(),((InfoVisitor*)v)->info());
    delete v;
}

TEST_F(VisitorTest,visitConpoundShape)
{
    v = new AreaVisitor();
    cs->accept(v);
    ASSERT_DOUBLE_EQ(cs->area(),((AreaVisitor*)v)->area());
    delete v;
    v = new InfoVisitor();
    cs->accept(v);
    ASSERT_EQ(cs->info(),((InfoVisitor*)v)->info());
    delete v;
}
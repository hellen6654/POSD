#include "../src/utility.h"
class UilityTest : public testing::Test
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
        shapes.push_back(r71);
        shapes.push_back(e87);

        shapes2.push_back(t142525);
        shapes2.push_back(r63);

        shapes3.push_back(r22);
        shapes3.push_back(r34);
        cs = new CompoundShape("9999", shapes);
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
};
TEST_F(UilityTest, CompoundShapeCreateIterator)
{
    Iterator *it = cs->createIterator();
    ASSERT_EQ(t72425->info(), (it->currentItem())->info());
    it->next();
    ASSERT_EQ(r71->info(), (it->currentItem())->info());
    ASSERT_TRUE(!(it->isDone()));
    it->next();
    it->next();
    ASSERT_TRUE(it->isDone());
    try
    {
        it->next();
    }
    catch (const std::string e)
    {
        ASSERT_EQ("Moving past the end!", e);
    }
}

TEST_F(UilityTest, GetShapeByIdInIterator)
{
    try
    {
        CompoundShape *cs = new CompoundShape("9999", shapes);
        CompoundShape *cs2 = new CompoundShape("999", shapes2);
        cs->addShape(cs2);
        cs->addShape(r22);
        Shape *s = getShapeById(cs, "3");
        ASSERT_EQ(r63->info(), s->info());
    }
    catch (const std::string &e)
    {
        std::cout << e << std::endl;
    }
}

TEST_F(UilityTest, GetShapeByIdInIteratorNotFindShape)
{
    try
    {
        CompoundShape *cs = new CompoundShape("9999", shapes);
        CompoundShape *cs2 = new CompoundShape("999", shapes2);
        cs->addShape(cs2);
        cs->addShape(r22);
        Shape *s = getShapeById(cs, "6");
    }
    catch (const std::string &e)
    {
        ASSERT_EQ("Expected get shape but shape not found",e);
    }
}

TEST_F(UilityTest, GetShapeByIdInIteratorNotCompoundShapeShape)
{
    try
    {
        Shape *s = getShapeById(r22, "6");
    }
    catch (const std::string &e)
    {
        ASSERT_EQ("Only compound shape can get shape!",e);
    }
}

TEST_F(UilityTest, FilterShapeByArea)
{
    Shape* s = new CompoundShape("123456",shapes);
    s->addShape(new CompoundShape("12345",shapes2));
    s->addShape(r22);
    s->addShape(r34);
    std::deque<Shape*> result = filterShape(s,AreaFilter(20,10));
    ASSERT_EQ(result[0]->info(),r63->info());
    ASSERT_EQ(result[1]->info(),r34->info());
}

TEST_F(UilityTest, FilterShapeByPerimeter)
{
    Shape* s = new CompoundShape("123456",shapes);
    s->addShape(new CompoundShape("12345",shapes2));
    s->addShape(r22);
    s->addShape(r34);
    std::deque<Shape*> result = filterShape(s,PerimeterFilter(20,10));
    ASSERT_EQ(result[0]->info(),r71->info());
    ASSERT_EQ(result[1]->info(),r63->info());
}

TEST_F(UilityTest, FilterShapeByColor)
{
    Shape* s = new CompoundShape("123456",shapes);
    s->addShape(new CompoundShape("12345",shapes2));
    s->addShape(r22);
    s->addShape(r34);
    std::deque<Shape*> result = filterShape(s,ColorFilter("green"));
    ASSERT_EQ(result[0]->info(),r63->info());
}

TEST_F(UilityTest, FilterShapeByType)
{
    Shape* s = new CompoundShape("123456",shapes);
    Shape* s1 = new CompoundShape("12345",shapes2);
    s->addShape(s1);
    s->addShape(r22);
    s->addShape(r34);
    std::deque<Shape*> result = filterShape(s,TypeFilter("Compound Shape"));
    ASSERT_EQ(result[0]->info(),s1->info());

    result = filterShape(s,TypeFilter("Ellipse"));
    ASSERT_EQ(result[0]->info(),e87->info());
}

TEST_F(UilityTest, FilterShapeError)
{
    try
    {
        std::deque<Shape*> result = filterShape(r34,AreaFilter(20,10));
    }
    catch(const std::string& e)
    {
        ASSERT_EQ("Only compound shape can filter shape!",e);
    }
}
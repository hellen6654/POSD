#include "../src/shape_filter.h"
#include "../src/shape_setter.h"

class FilterTest : public testing::Test
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

        t72425 = new Triangle("0", pointsA, "red");
        /* perimeter = 56 / area = 84  */

        r71 = new Rectangle("2", 7, 1, "yellow");
        /* perimeter = 16 / area = 7  */

        e87 = new Ellipse("4", 8, 7, "blue");
        /* perimeter = 47.982 / area = 175.929 */

        t142525 = new Triangle("1", pointsB, "orange");
        /* perimeter = 64 / area = 168  */

        r63 = new Rectangle("3", 6, 3, "green");
        /* perimeter = 18 / area = 18  */

        r22 = new Rectangle("5", 2, 2, "pink");
        /* perimeter = 8 / area = 4 */

        r34 = new Rectangle("6", 3, 4, "purple");
        /* perimeter = 14 / area = 12 */
        shapes.push_back(t72425);
        shapes.push_back(r71);
        shapes.push_back(e87);
        shapes.push_back(t142525);
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
    }
    std::list<Shape *> shapes;
    std::list<Shape *> shapes2;
    Shape *t72425;
    Shape *t142525;
    Shape *r71;
    Shape *r63;
    Shape *e87;
    Shape *r22;
    Shape *r34;
    Filter *areaFilter;
    Filter *perimeterFilter;
    Filter *colorFilter;
    Filter *colorSetter;
};

TEST_F(FilterTest, FilterOneLayer)
{
    areaFilter = new ShapeFilter([](Shape *shape) { return shape->area() < 170; });

    std::list<Shape *> result = areaFilter->push(shapes);
    ASSERT_EQ(3, result.size());
    auto it = result.begin();
    ASSERT_DOUBLE_EQ(84, (*it)->area());
    ASSERT_DOUBLE_EQ(56, (*it)->perimeter());
    ASSERT_EQ("red", (*it)->color());
    ASSERT_EQ("0", (*it)->id());
    it++;
    ASSERT_DOUBLE_EQ(7, (*it)->area());
    ASSERT_DOUBLE_EQ(16, (*it)->perimeter());
    ASSERT_EQ("yellow", (*it)->color());
    ASSERT_EQ("2", (*it)->id());
    it++;
    ASSERT_DOUBLE_EQ(168, (*it)->area());
    ASSERT_DOUBLE_EQ(64, (*it)->perimeter());
    ASSERT_EQ("orange", (*it)->color());
    ASSERT_EQ("1", (*it)->id());
}

TEST_F(FilterTest, FilterTwoLayer)
{
    areaFilter = new ShapeFilter([](Shape *shape) { return shape->area() < 170; });
    perimeterFilter = new ShapeFilter([](Shape *shape) { return shape->perimeter() < 60; });

    areaFilter->setNext(perimeterFilter);

    std::list<Shape *> result = areaFilter->push(shapes);
    ASSERT_EQ(2, result.size());
    auto it = result.begin();
    ASSERT_DOUBLE_EQ(84, (*it)->area());
    ASSERT_DOUBLE_EQ(56, (*it)->perimeter());
    ASSERT_EQ("red", (*it)->color());
    ASSERT_EQ("0", (*it)->id());
    it++;
    ASSERT_DOUBLE_EQ(7, (*it)->area());
    ASSERT_DOUBLE_EQ(16, (*it)->perimeter());
    ASSERT_EQ("yellow", (*it)->color());
    ASSERT_EQ("2", (*it)->id());
}

TEST_F(FilterTest, FilterThreeLayer)
{
    areaFilter = new ShapeFilter([](Shape *shape) { return shape->area() < 170; });
    perimeterFilter = new ShapeFilter([](Shape *shape) { return shape->perimeter() < 60; });
    colorFilter = new ShapeFilter([](Shape *shape) { return shape->color() == "red"; });

    areaFilter->setNext(perimeterFilter)->setNext(colorFilter);

    std::list<Shape *> result = areaFilter->push(shapes);
    ASSERT_EQ(1, result.size());
    auto it = result.begin();
    ASSERT_DOUBLE_EQ(84, (*it)->area());
    ASSERT_DOUBLE_EQ(56, (*it)->perimeter());
    ASSERT_EQ("red", (*it)->color());
    ASSERT_EQ("0", (*it)->id());
}

TEST_F(FilterTest, FilterThreeLayerAndChengeColor)
{
    areaFilter = new ShapeFilter([](Shape *shape) { return shape->area() < 170; });
    perimeterFilter = new ShapeFilter([](Shape *shape) { return shape->perimeter() < 60; });
    colorFilter = new ShapeFilter([](Shape *shape) { return shape->color() == "red"; });
    colorSetter = new ShapeSetter([](Shape *shape) { shape->setColor("black"); });
    
    areaFilter->setNext(perimeterFilter)->setNext(colorFilter)->setNext(colorSetter);

    std::list<Shape *> result = areaFilter->push(shapes);
    ASSERT_EQ(1, result.size());
    auto it = result.begin();
    ASSERT_DOUBLE_EQ(84, (*it)->area());
    ASSERT_DOUBLE_EQ(56, (*it)->perimeter());
    ASSERT_EQ("black", (*it)->color());
    ASSERT_EQ("0", (*it)->id());
}

TEST_F(FilterTest, FilterTwoLayerAndChengeColor)
{
    areaFilter = new ShapeFilter([](Shape *shape) { return shape->area() < 170; });
    perimeterFilter = new ShapeFilter([](Shape *shape) { return shape->perimeter() < 60; });
    colorSetter = new ShapeSetter([](Shape *shape) { shape->setColor("black"); });
    
    areaFilter->setNext(perimeterFilter)->setNext(colorSetter);

    std::list<Shape *> result = areaFilter->push(shapes);
    ASSERT_EQ(2, result.size());
    auto it = result.begin();
    ASSERT_DOUBLE_EQ(84, (*it)->area());
    ASSERT_DOUBLE_EQ(56, (*it)->perimeter());
    ASSERT_EQ("black", (*it)->color());
    ASSERT_EQ("0", (*it)->id());
    it++;
    ASSERT_DOUBLE_EQ(7, (*it)->area());
    ASSERT_DOUBLE_EQ(16, (*it)->perimeter());
    ASSERT_EQ("black", (*it)->color());
    ASSERT_EQ("2", (*it)->id());
}

TEST_F(FilterTest, FilterOneLayerAndChangeColor)
{
    areaFilter = new ShapeFilter([](Shape *shape) { return shape->area() < 170; });
    colorSetter = new ShapeSetter([](Shape *shape) { shape->setColor("black"); });

    areaFilter->setNext(colorSetter);

    std::list<Shape *> result = areaFilter->push(shapes);
    ASSERT_EQ(3, result.size());
    auto it = result.begin();
    ASSERT_DOUBLE_EQ(84, (*it)->area());
    ASSERT_DOUBLE_EQ(56, (*it)->perimeter());
    ASSERT_EQ("black", (*it)->color());
    ASSERT_EQ("0", (*it)->id());
    it++;
    ASSERT_DOUBLE_EQ(7, (*it)->area());
    ASSERT_DOUBLE_EQ(16, (*it)->perimeter());
    ASSERT_EQ("black", (*it)->color());
    ASSERT_EQ("2", (*it)->id());
    it++;
    ASSERT_DOUBLE_EQ(168, (*it)->area());
    ASSERT_DOUBLE_EQ(64, (*it)->perimeter());
    ASSERT_EQ("black", (*it)->color());
    ASSERT_EQ("1", (*it)->id());
}
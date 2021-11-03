#include <array>
#include "../src/sort.h"
#include "../src/rectangle.h"
#include "../src/triangle.h"

class ShapeSort : public testing::Test
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

        t72425 = new Triangle(pointsA);
        /* perimeter = 56 / area = 84  */

        t142525 = new Triangle(pointsB);
        /* perimeter = 64 / area = 168  */

        r71 = new Rectangle(7, 1);
        /* perimeter = 16 / area = 7  */

        r63 = new Rectangle(6, 3);
        /* perimeter = 18 / area = 18  */

    }

    void TearDown() override
    {
        delete t72425;
        delete t142525;
        delete r71;
        delete r63;
    }
    double ascendingPerimeter[4] = {16,18,56,64 };
    double ascendingArea[4]={7,18,84,168};
    double descendingPerimeter[4]={64,56,18,16};
    double descendingArea[4]={168,84,18,7};
    Shape *t72425;
    Shape *t142525;
    Shape *r71;
    Shape *r63;
};

TEST_F(ShapeSort, SubtypePolymorphism)
{
    Shape *shapes[4] = {t72425, t142525, r71, r63};
    ASSERT_EQ(84, shapes[0]->area());
    ASSERT_EQ(64, shapes[1]->perimeter());
    ASSERT_EQ(7, shapes[2]->area());
    ASSERT_EQ(18, shapes[3]->perimeter());
}

// =============================================== //
// ================ ByFunction =================== //
// =============================================== //

TEST_F(ShapeSort, AscendingPerimeterByFunc)
{
    
    Shape* shapes[4] = {t72425, t142525, r71, r63};
    quickSort(shapes, shapes+4,perimeterAscendingCompare);
    for(int i=0;i < 4;i++) 
        ASSERT_EQ(ascendingPerimeter[i],shapes[i]->perimeter());
}

TEST_F(ShapeSort, DecendingPerimeterByFunc)
{
    Shape *shapes[4] = {t72425, t142525, r71, r63};
    quickSort(shapes, shapes+4,perimeterDescendingCompare);
    for(int i=0;i < 4;i++) 
        ASSERT_EQ(descendingPerimeter[i],shapes[i]->perimeter());
}

TEST_F(ShapeSort, AscendingAreaByFunc)
{
    Shape *shapes[4] = {t72425, t142525, r71, r63};
    quickSort(shapes, shapes+4,areaAscendingCompare);
    for(int i=0;i < 4;i++) 
        ASSERT_EQ(ascendingArea[i],shapes[i]->area());
}

TEST_F(ShapeSort, DecendingAreaByFunc)
{
    Shape *shapes[4] = {t72425, t142525, r71, r63};
    quickSort(shapes, shapes+4,areaDescendingCompare);
    for(int i=0;i < 4;i++) 
        ASSERT_EQ(descendingArea[i],shapes[i]->area());
}

// // =============================================== //
// // ================= By Obj ====================== //
// // =============================================== //

TEST_F(ShapeSort, AscendingPerimeterByObj)
{
    Shape *shapes[4] = {t72425, t142525, r71, r63};
    AscendingCompare as("perimeter");
    quickSort(shapes,shapes+4,as);
    for(int i=0;i < 4;i++) 
        ASSERT_EQ(ascendingPerimeter[i],shapes[i]->perimeter());
}

TEST_F(ShapeSort, DecendingPerimeterByObj)
{
    Shape *shapes[4] = {t72425, t142525, r71, r63};
    DescendingCompare as("perimeter");
    quickSort(shapes,shapes+4,as);
    for(int i=0;i < 4;i++) 
        ASSERT_EQ(descendingPerimeter[i],shapes[i]->perimeter());
}

TEST_F(ShapeSort, AscendingAreaByObj)
{
    Shape *shapes[4] = {t72425, t142525, r71, r63};
    AscendingCompare as("area");
    quickSort(shapes,shapes+4,as);
    for(int i=0;i < 4;i++) 
        ASSERT_EQ(ascendingArea[i],shapes[i]->area());
}

TEST_F(ShapeSort, DecendingAreaByObj)
{
    Shape *shapes[4] = {t72425, t142525, r71, r63};
    DescendingCompare as("area");
    quickSort(shapes,shapes+4,as);
    for(int i=0;i < 4;i++) 
        ASSERT_EQ(descendingArea[i],shapes[i]->area());
}

// =============================================== //
// =============== By Lambda ===================== //
// =============================================== //

TEST_F(ShapeSort, AscendingPerimeterByLambda)
{
    Shape *shapes[4] = {t72425, t142525, r71, r63};
    quickSort(shapes, shapes+4,[](Shape * a, Shape * b) { return a->perimeter() < b->perimeter(); });
    for(int i=0;i < 4;i++) 
        ASSERT_EQ(ascendingPerimeter[i],shapes[i]->perimeter());
}

TEST_F(ShapeSort, DecendingPerimeterByLambda)
{
    Shape *shapes[4] = {t72425, t142525, r71, r63};
    quickSort(shapes, shapes+4,[](Shape * a, Shape * b) { return a->perimeter() > b->perimeter(); });
    for(int i=0;i < 4;i++) 
        ASSERT_EQ(descendingPerimeter[i],shapes[i]->perimeter());
}

TEST_F(ShapeSort, AscendingAreaByLambda)
{
    Shape *shapes[4] = {t72425, t142525, r71, r63};
    quickSort(shapes, shapes+4,[](Shape * a, Shape * b) { return a->area() < b->area(); });
    for(int i=0;i < 4;i++) 
        ASSERT_EQ(ascendingArea[i],shapes[i]->area());
}

TEST_F(ShapeSort, DecendingAreaByLambda)
{
    Shape *shapes[4] = {t72425, t142525, r71, r63};
    quickSort(shapes, shapes+4,[](Shape * a, Shape * b) { return a->area() > b->area(); });
    for(int i=0;i < 4;i++) 
        ASSERT_EQ(descendingArea[i],shapes[i]->area());
}
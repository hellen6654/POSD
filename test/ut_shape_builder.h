#include "../src/shape_builder.h"

TEST(ShapeBuilderTest, buildTriangle) {
    ShapeBuilder sb;
    sb.buildTriangle(0, 0, 0, -3, -4, 0);
    std::deque<Shape*> results = sb.getResult();

    ASSERT_EQ(1, results.size());
    ASSERT_EQ("Triangle ([0.000, 0.000], [0.000, -3.000], [-4.000, 0.000])", results[0]->info());
}

TEST(ShapeBuilderTest, buildRectangle) {
    ShapeBuilder sb;
    sb.buildRectangle(3,4);
    std::deque<Shape*> results = sb.getResult();

    ASSERT_EQ(1, results.size());
    ASSERT_EQ("Rectangle (3.000, 4.000)", results[0]->info());
}

TEST(ShapeBuilderTest, buildEllipse) {
    ShapeBuilder sb;
    sb.buildEllipse(4,3);
    std::deque<Shape*> results = sb.getResult();
    ASSERT_EQ(1, results.size());
    ASSERT_EQ("Ellipse (4.000, 3.000)", results[0]->info());
}
TEST(ShapeBuilderTest, buildEmptyCompoundShape) {
    ShapeBuilder sb;
    sb.buildCompoundShapeBegin();
    sb.buildCompoundShapeEnd();
    
    std::deque<Shape*> results = sb.getResult();

    ASSERT_EQ(1, results.size());
    ASSERT_EQ("Compound Shape {}", results[0]->info());
}

TEST(ShapeBuilderTest, buildOneCompoundshape) {
    ShapeBuilder sb;
    sb.buildCompoundShapeBegin();
    sb.buildTriangle(0, 0, 0, -3, -4, 0);
    sb.buildCompoundShapeEnd();
    std::deque<Shape*> results = sb.getResult();

    ASSERT_EQ(1, results.size());
    ASSERT_EQ("Compound Shape {Triangle ([0.000, 0.000], [0.000, -3.000], [-4.000, 0.000])}", results[0]->info());
}

TEST(ShapeBuilderTest, buildCompoundshapeOfCompoundshape) {
    ShapeBuilder sb;
    sb.buildCompoundShapeBegin();
    sb.buildTriangle(0, 0, 0, -3, -4, 0);
    sb.buildCompoundShapeBegin();
    sb.buildTriangle(0, 0, 0, -3, -4, 0);
    sb.buildCompoundShapeEnd();
    sb.buildCompoundShapeEnd();
    std::deque<Shape*> results = sb.getResult();

    ASSERT_EQ(1, results.size());
    ASSERT_EQ("Compound Shape {Triangle ([0.000, 0.000], [0.000, -3.000], [-4.000, 0.000]), Compound Shape {Triangle ([0.000, 0.000], [0.000, -3.000], [-4.000, 0.000])}}", results[0]->info());
}


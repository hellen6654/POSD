#include "../src/shape_parser.h"

TEST(ShapeParserTest, Triangle) {
    ShapeParser sp("Triangle (0.000, 0.000, 0.000, -3.000, -4.000, 0.000)");
    sp.parser();

    std::deque<Shape*> results = sp.getResult();

    ASSERT_EQ(1, results.size());
    ASSERT_EQ("Triangle ([0.000, 0.000], [0.000, -3.000], [-4.000, 0.000])", results[0]->info());
}

TEST(ShapeParserTest, Rectangle) {
    ShapeParser sp("Rectangle (3.000, 4.000)");
    sp.parser();

    std::deque<Shape*> results = sp.getResult();

    ASSERT_EQ(1, results.size());
    ASSERT_EQ("Rectangle (3.000, 4.000)", results[0]->info());
}

TEST(ShapeParserTest, Ellipse) {
    ShapeParser sp("Ellipse (4.000, 3.000)");
    sp.parser();

    std::deque<Shape*> results = sp.getResult();

    ASSERT_EQ(1, results.size());
    ASSERT_EQ("Ellipse (4.000, 3.000)", results[0]->info());
}

TEST(ShapeParserTest, EllipseAndRectangle) {
    ShapeParser sp("Ellipse (4.000, 3.000), Rectangle (3.000, 4.000)");
    sp.parser();

    std::deque<Shape*> results = sp.getResult();

    ASSERT_EQ(2, results.size());
    ASSERT_EQ("Ellipse (4.000, 3.000)", results[0]->info());
    ASSERT_EQ("Rectangle (3.000, 4.000)", results[1]->info());
}

TEST(ShapeParserTest, parser_multi_simple_shapes_with_one_shape_contain_invalid_argument_that_should_be_ignored) {

    ShapeParser sp("Rectangle (3.000, 4.000), Ellipse (4.200, 3.700), Ellipse (4.200, 3.700, 12.502), Triangle (0.000, 0.000, 0.000, -3.000, -4.000, 0.000)");
    sp.parser();

    std::deque<Shape*> results = sp.getResult();

    ASSERT_EQ(3, results.size());

    EXPECT_EQ("Rectangle (3.000, 4.000)", results[0]->info());
    EXPECT_EQ("Ellipse (4.200, 3.700)", results[1]->info());
    EXPECT_EQ("Triangle ([0.000, 0.000], [0.000, -3.000], [-4.000, 0.000])", results[2]->info());
}

TEST(ShapeParserTest, CompoundShape) {
    ShapeParser sp("CompoundShape {Ellipse (4.000, 3.000)}");
    sp.parser();

    std::deque<Shape*> results = sp.getResult();

    ASSERT_EQ(1, results.size());
    ASSERT_EQ("Compound Shape {Ellipse (4.000, 3.000)}", results[0]->info());
}

TEST(ShapeParserTest, CompoundShape_error) {
    ShapeParser sp("CompoundShape {Ellipse (4.000), Ellipse (4.000, 3.000)}");
    sp.parser();

    std::deque<Shape*> results = sp.getResult();

    ASSERT_EQ(1, results.size());
    ASSERT_EQ("Compound Shape {Ellipse (4.000, 3.000)}", results[0]->info());
}

TEST(ShapeParserTest, CompoundShapeOfCompoundShape) {
    ShapeParser sp("CompoundShape {Ellipse (4.000), CompoundShape {Ellipse (4.000, 3.000)}}, Ellipse (4.000, 3.000)");
    sp.parser();

    std::deque<Shape*> results = sp.getResult();

    ASSERT_EQ(2, results.size());
    ASSERT_EQ("Compound Shape {Compound Shape {Ellipse (4.000, 3.000)}}", results[0]->info());
    ASSERT_EQ("Ellipse (4.000, 3.000)", results[1]->info());
}
#include "../src/scanner.h"

TEST(Scanner, ellipse) {
    Scanner scanner("Ellipse (4.000, 3.000)");

    ASSERT_EQ("Ellipse", scanner.nextToken());
    ASSERT_EQ("(", scanner.nextToken());
    ASSERT_EQ("4.000", scanner.nextToken());
    ASSERT_EQ(",", scanner.nextToken());
    ASSERT_EQ("3.000", scanner.nextToken());
    ASSERT_EQ(")", scanner.nextToken());

    try {
        scanner.nextToken();
        FAIL();
    }catch(std::string e) {
        ASSERT_EQ("next char doesn't exist.", e);
    }
}

TEST(Scanner, triangle) {
    Scanner scanner("Triangle (0.000, 0.000, -3.000, 0.000, 0.000, -4.000)");

    ASSERT_EQ("Triangle", scanner.nextToken());
    ASSERT_EQ("(", scanner.nextToken());
    ASSERT_EQ("0.000", scanner.nextToken());
    ASSERT_EQ(",", scanner.nextToken());
    ASSERT_EQ("0.000", scanner.nextToken());
    ASSERT_EQ(",", scanner.nextToken());
    ASSERT_EQ("-3.000", scanner.nextToken());
    ASSERT_EQ(",", scanner.nextToken());
    ASSERT_EQ("0.000", scanner.nextToken());
    ASSERT_EQ(",", scanner.nextToken());
    ASSERT_EQ("0.000", scanner.nextToken());
    ASSERT_EQ(",", scanner.nextToken());
    ASSERT_EQ("-4.000", scanner.nextToken());
    ASSERT_EQ(")", scanner.nextToken());

    try {
        scanner.nextToken();
        FAIL();
    }catch(std::string e) {
        ASSERT_EQ("next char doesn't exist.", e);
    }
}

TEST(Scanner, rectangle) {
    Scanner scanner("Rectangle (3.000, 4.000)");

    ASSERT_EQ("Rectangle", scanner.nextToken());
    ASSERT_EQ("(", scanner.nextToken());
    ASSERT_EQ("3.000", scanner.nextToken());
    ASSERT_EQ(",", scanner.nextToken());
    ASSERT_EQ("4.000", scanner.nextToken());
    ASSERT_EQ(")", scanner.nextToken());

    try {
        scanner.nextToken();
        FAIL();
    }catch(std::string e) {
        ASSERT_EQ("next char doesn't exist.", e);
    }
}

TEST(Scanner, compoundshape) {
    Scanner scanner("CompoundShape {Ellipse (4.000, 3.000)}");

    ASSERT_EQ("CompoundShape", scanner.nextToken());
    ASSERT_EQ("{", scanner.nextToken());
    ASSERT_EQ("Ellipse", scanner.nextToken());
    ASSERT_EQ("(", scanner.nextToken());
    ASSERT_EQ("4.000", scanner.nextToken());
    ASSERT_EQ(",", scanner.nextToken());
    ASSERT_EQ("3.000", scanner.nextToken());
    ASSERT_EQ(")", scanner.nextToken());
    ASSERT_EQ("}", scanner.nextToken());

    try {
        scanner.nextToken();
        FAIL();
    }catch(std::string e) {
        ASSERT_EQ("next char doesn't exist.", e);
    }
}

TEST(Scanner, ErrorShape) {
    Scanner scanner("Ellipse (4.200, 3.700, 12.502)");

    ASSERT_EQ("Ellipse", scanner.nextToken());
    ASSERT_EQ("(", scanner.nextToken());
    ASSERT_EQ("4.200", scanner.nextToken());
    ASSERT_EQ(",", scanner.nextToken());
    ASSERT_EQ("3.700", scanner.nextToken());
    ASSERT_EQ(",", scanner.nextToken());
    ASSERT_EQ("12.502", scanner.nextToken());
    ASSERT_EQ(")", scanner.nextToken());
    try {
        scanner.nextToken();
        FAIL();
    }catch(std::string e) {
        ASSERT_EQ("next char doesn't exist.", e);
    }
}
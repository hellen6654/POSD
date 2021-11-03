#include "../src/null_iterator.h"
#include "../src/shape_iterator.h"
#include "../src/shape.h"

TEST(NULLITERATOR, NullIteratorFirst)
{
    NullIterator *p = new NullIterator();
    try
    {
        p->first();
    }
    catch (const std::string e)
    {
        ASSERT_EQ("No child member!", e);
    }
}

TEST(NULLITERATOR, NullIteratorNext)
{
    NullIterator *p = new NullIterator();
    try
    {
        p->next();
    }
    catch (const std::string e)
    {
        ASSERT_EQ("No child member!", e);
    }
}

TEST(NULLITERATOR, NullIteratorIsDone)
{
    NullIterator *p = new NullIterator();
    ASSERT_TRUE(p->isDone());
}

TEST(NULLITERATOR, NullIteratorCurrentItem)
{
    NullIterator *p = new NullIterator();
    try
    {
        p->currentItem();
    }
    catch (const std::string e)
    {
        ASSERT_EQ("No child member!", e);
    }
}

TEST(SHAPEITERATOR, IteratorFirst)
{
    Shape *r71 = new Rectangle("2", 7, 1, "yellow");
    Shape *r63 = new Rectangle("3", 6, 3, "green");
    std::list<Shape *> shapes{r71, r63};
    CompoundShape cs("3549", shapes);
    Iterator *p = cs.createIterator();

    ASSERT_EQ(r71->info(), p->currentItem()->info());
    ASSERT_TRUE(!p->isDone());
}

TEST(SHAPEITERATOR, IteratorNextAndIsDone)
{
    Shape *r71 = new Rectangle("2", 7, 1, "yellow");
    Shape *r63 = new Rectangle("3", 6, 3, "green");
    std::list<Shape *> shapes{r71, r63};
    CompoundShape cs("3549", shapes);
    Iterator *p = cs.createIterator();
    p->next();
    ASSERT_EQ(r63->info(), p->currentItem()->info());
    p->next();
    ASSERT_TRUE(p->isDone());
}

TEST(SHAPEITERATOR, IteratorDoneAndFirst)
{
    Shape *r71 = new Rectangle("2", 7, 1, "yellow");
    Shape *r63 = new Rectangle("3", 6, 3, "green");
    std::list<Shape *> shapes{r71, r63};
    CompoundShape cs("3549", shapes);
    Iterator *p = cs.createIterator();
    p->next();
    ASSERT_EQ(r63->info(), p->currentItem()->info());
    p->next();
    ASSERT_TRUE(p->isDone());
    p->first();
    ASSERT_EQ(r71->info(), p->currentItem()->info());
}

TEST(SHAPEITERATOR, NullIteratorCurrentItem)
{
    NullIterator *p = new NullIterator();
    try
    {
        p->currentItem();
    }
    catch (const std::string e)
    {
        ASSERT_EQ("No child member!", e);
    }
}

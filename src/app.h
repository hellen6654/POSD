#ifndef APP_H
#define APP_H
#include "node.h"
#include "null_iterator.h"

class App : public Node
{
public:
    App();
    App(std::string id, std::string name, double size)
    {
        _id = id;
        _name = name;
        _size = size;
        _path = "";
    }
    // implement any functions inherit from Node that you think is suitable.
};
#endif
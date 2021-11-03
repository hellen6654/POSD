#ifndef APP_H
#define APP_H
#include "node.h"
#include "null_iterator.h"
#include "visitor.h"

class App : public Node
{
public:
    App(std::string id, std::string name, double size) : Node(id,name,size)
    { }
    void accept(Visitor* visitor)
    {
        visitor->visitApp(this);
    }   
};
#endif
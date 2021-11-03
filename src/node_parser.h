#include <deque>
#include <iostream>
#include "app.h"
#include "folder.h"
#include "node_builder.h"
#include "node_scanner.h"

class NodeParser
{
public:
    NodeParser(std::string input)
    {
        // initialize a scanner for handling input.
        // initialize a node builder for handling building node.
        s = new NodeScanner(input);
        b = new NodeBuilder();
    }

    void parser()
    {
        // using NodeScanner::nextToken() to get all information to determine what to build,
        // and provide the argument the node needed.
        // use functions in NodeBuilder to build out the node.
        // the node with invalid argument should be ignored.
        std::string str = "";
        std::string temp = "";
        while (1)
        {
            std::vector<std::string> arg;
            try
            {
                str = s->nextToken();
                if (str == "(")
                {
                    while ((str = s->nextToken()) != ")")
                    {
                        arg.push_back(str);
                    }
                    try
                    {
                        if (!arg.empty() && arg.size() == 1)
                            b->buildApp(temp, stod(arg[0]));
                    }
                    catch (const std::exception &e)
                    {
                    }
                }
                else if (str == "{" && temp != "," && temp!=")" && temp!="(" && temp!="}")
                {
                    b->buildFolderBegin(temp);
                }
                else if (str =="}")
                {
                    b->buildFolderEnd();
                }
                temp = str; //be used to save nodeName
            }
            catch (const std::string e)
            {
                break;
            }
        }
        _result = b->getResult();
    }

    std::deque<Node *> getResult()
    {
        // return result. 
        return _result;
    }

private:
    NodeScanner *s;
    NodeBuilder *b;
    std::deque<Node *> _result;
};

#ifndef NODE_BUILDER_H
#define NODE_BUILDER_H
#include <algorithm>
#include <iostream>
#include <vector>
#include <deque>
#include <stack>
#include "folder.h"
#include "app.h"

class NodeBuilder
{
public:
    void buildApp(std::string name, double size)
    {
        // build a app with an unique id and push in a std::stack.
        _stack.push(new App(std::to_string(count++), name, size));
    }

    void buildFolderBegin(std::string name)
    {
        // notify begin of folder.
        _stack.push(new Folder(std::to_string(count++), name));
    }

    void buildFolderEnd()
    {
        // notify end of folder.
        std::stack<Node*> temp;
        Node *n;
        while (!_stack.empty())
        {
            n = _stack.top();
            _stack.pop();
            if (std::find(folderId.begin(),folderId.end(),n->id()) != folderId.end() || n->size()!=0)
            {
                temp.push(n);
            }   
            else if (n->size() == 0)
            {
                //folder
                while (!temp.empty())
                {
                    Node *nn = temp.top();
                    temp.pop();
                    n->addNode(nn);
                }
                temp.push(n);
                folderId.push_back(n->id());
                break; //防止跑過頭 連前面的folder都一起建立
            }
        }

        while (!temp.empty())
        {
            _stack.push(temp.top());
            temp.pop();
        }
    }

    std::deque<Node *> getResult()
    {
        // return result.
        while (!_stack.empty())
        {
            _result.push_front(_stack.top());
            _stack.pop();
        }
        return _result;
    }

private:
    int count = 0;
    std::vector<std::string> folderId;
    std::stack<Node *> _stack;
    std::deque<Node *> _result;
};
#endif
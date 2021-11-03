#ifndef FOLDER_H
#define FOLDER_H
#include <list>
#include <iostream>
#include "node.h"
#include "node_iterator.h"

class Folder : public Node
{
public:
    Folder() {}
    Folder(std::string id, std::string name)
    {
        // the default size of folder is zero.
        _id = id;
        _name = name;
        _size = 0.0;
        _path = "";
    }
    double size() const
    {
        double result = 0.0;
        for (auto it : _nodes)
            result += it->size();
        return result;
    }
    void updatePath(std::string path)
    {
        _path = path;
        for (auto it : _nodes)
        {
            it->updatePath(path);
        }
    }

    void addNode(Node *node)
    {
        Iterator *it = node->createIterator();
        try
        {
            it->first();
            //node 是個folder
            node->updatePath(this->route());
            for (it->first(); !it->isDone(); it->next())
            {
                //folder內的node做update
                it->currentItem()->updatePath(node->route());
                //要是這個node也是個folder在去對他底下的node做update
                try
                {
                    Iterator *it2 = it->currentItem()->createIterator();
                    it2->first();
                    for (it2->first(); !it2->isDone(); it2->next())
                    {
                        it2->currentItem()->updatePath(it->currentItem()->route());
                    }
                    //底下是個folder
                }
                catch (std::string s)
                {
                }
            }
        }
        catch (std::string e)
        {
            //這邊是個node
            node->updatePath(this->route());
        }
        //node->updatePath(this->route());
        _nodes.push_back(node);
    }

    Node *getNodeById(std::string id) const
    {
        for (auto it : _nodes)
        {
            try
            {
                return (it)->getNodeById(id);
            }
            catch (const std::string e)
            {
            }
            if ((it)->id() == id)
                return (it);
        }
        throw std::string("Expected get node but node not found.");
    }

    void deleteNodeById(std::string id)
    {
        for (auto it : _nodes)
        {
            try
            {
                return (it)->deleteNodeById(id);
            }
            catch (const std::string e)
            {
            }
            if (it->id() == id)
            {
                _nodes.remove(it);
                return;
            }
        }
        throw std::string("Expected delete node but node not found.");
    }
    Iterator *createIterator() const
    {
        return new NodeIterator<std::list<Node *>::const_iterator>(_nodes.begin(), _nodes.end());
    }

    // implement any functions inherit from Node that you think is suitable.

private:
    std::list<Node *> _nodes;
};
#endif
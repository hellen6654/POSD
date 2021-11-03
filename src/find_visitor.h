#include "visitor.h"
#include "app.h"
#include "folder.h"
#include "iterator.h"

class FindVisitor : public Visitor
{
public:
    FindVisitor(std::string name)
    {
        _name = name;
    }

    void visitApp(App *app)
    {
        // find app when app's name matches given name,
        // add app's route as result.
        if (app->name() == _name)
            _result = app->route();
    }

    void visitFolder(Folder *folder)
    {
        // find folder when folder's name matches given name,
        // add folder's route as result.
        // And find the tree structure bellow,
        // add the other match result with `\n`.
        if (folder->name() == _name)
            _result = folder->route();

        Iterator *it = folder->createIterator();

        while (!it->isDone())
        {
            FindVisitor *v = new FindVisitor(_name);
            it->currentItem()->accept(v);
            if (v->getResult() != "")
            {
                if (_result != "")
                    _result += '\n' + v->getResult();
                else
                    _result += v->getResult();
            }
            it->next();
            delete v;
        }
    }
    std::string getResult() const
    {
        // return result.
        return _result;
    }

private:
    std::string _name;
    std::string _result;
};
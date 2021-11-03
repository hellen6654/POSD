#ifndef NODE_SCANNER_H
#define NODE_SCANNER_H
#include <iostream>
#include <deque>
#include <ctype.h>

class NodeScanner {
public:
    NodeScanner(std::string input) :_input(input) 
    {
        //"Node_Name", "Node_Size", '{', '}', '(', ')', ','
        std::reverse(input.begin(), input.end());
        std::string temp = "";
        char p = ' ';
        while (1)
        {
            p = input.back();
            if (p == '\0')
                break;
            else if (p == ' ')
            {
                if (temp != "")
                    _token.push_back(temp);
                temp = "";
            }
            else if (p == '{' || p == '}' || p == ',' || p == '(' || p == ')')
            {
                std::string sign{p};
                if (temp != "")
                    _token.push_back(temp);
                if (p != ' ')
                    _token.push_back(sign);
                temp = "";
            }
            else if(isalnum(p)|| p=='.')
            {
                temp += p;
            }
            input.pop_back();
        }
    }
    std::string nextToken() 
    {
        // return next token.
        // throw exception std::string "next token doesn't exist." if next token not found.
        if(_token.empty())
            throw std::string("next token doesn't exist.");
        std::string result = _token[0];
        _token.pop_front();
        return result;
    }

    // you can add other public functions if you needed.
    private:
    std::string _input;
    std::deque<std::string> _token;
};
#endif
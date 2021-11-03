#ifndef SCANNER_H
#define SCANNER_H

#include <string>
#include <iostream>
#include <algorithm>
#include <deque>


class Scanner
{
public:
    Scanner(std::string input) : _input(input)
    {
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
                    _result.push_back(temp);
                temp = "";
            }
            else if (p == '{' || p == '}' || p == ',' || p == '(' || p == ')')
            {
                std::string sign{p};
                if (temp != "")
                    _result.push_back(temp);
                if (p != ' ')
                    _result.push_back(sign);
                temp = "";
            }
            else
            {
                temp += p;
            }
            input.pop_back();
        }
    }

    std::string nextToken()
    {
        // return next token.
        // throw exception std::string "next char doesn't exist." if next token not found.
        if (_result.size() == 0)
            throw std::string("next char doesn't exist.");
        std::string token = _result[0];
        _result.pop_front();
        return token;
    }

private:
    std::string _input;
    std::deque<std::string> _result;
};

#endif
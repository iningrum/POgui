#pragma once
#include <string>
#include <array>
#include <iostream>
#include <vector>
std::string strip(std::string str)
{
    std::string::iterator start = str.begin();
    std::string::reverse_iterator end = str.rbegin();
    while (*start == ' ' || *start == '\t' || *start == '\n')
        start++;
    while (*end == ' ' || *end == '\t' || *start == '\n')
        end++;
    return std::string(start, end.base());
}
std::vector<std::string> split(std::string str,char c)
{
    str+=',';
    std::string substr;
    std::vector<std::string> result;
    for(auto v:str)
    {
        if(v==c)
        {
            result.push_back(substr);
            substr.clear();
            continue;
        } 
        substr+=v;
    }
    for (auto s:result)
    {
        std::cout << "\n\t\t" << s << "\n";
    }
    return result;
}

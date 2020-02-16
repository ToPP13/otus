#pragma once
#include <string>
#include <vector>
#include <array>
#include <iostream>

int version();

bool revert_lex_sort(std::string first, std::string second);

std::vector<std::string> split(const std::string &str, char d);


struct Ip{
    Ip(std::vector<int> data)
    {
        components.reserve(data.size());
        components = data;
    }
    Ip(std::vector<int> && data)
    {
        components.reserve(data.size());
        components = data;
    }
    bool operator == (const Ip &Ref) const
    {
        return(this->components == Ref.components);
    }
    void print()
    {
        for(auto ip_part = this->components.cbegin(); ip_part != this->components.cend(); ++ip_part)
        {
            if (ip_part != this->components.cbegin())
            {
                std::cout << ".";
            }
            std::cout << *ip_part;
        }
    }
    std::vector<int> components;
};

void print_ip_pool(std::vector<Ip> ip_pool);

std::vector<Ip> filter(std::vector<Ip> filter_list);


template<typename CI,typename T>
bool filter_elem(CI ci, T cur_param)
{
    if (*ci != cur_param)
        return false;
    return true;
}

template<typename CI,typename T, typename... Args>
bool filter_elem(CI ci, T cur_param, Args... args)
{
    if (*ci != cur_param)
        return false;
    return filter_elem(++ci, args...);
}

template<typename... Args>
std::vector<Ip> filter(std::vector<Ip> filter_list, Args... args)
{
    std::vector<Ip> res;
    auto args_size = sizeof...(args);

    for(auto ip : filter_list)
    {
        if (ip.components.size() < args_size)
            continue;
        if (filter_elem(ip.components.begin(), args...))
        {
            res.push_back(ip);
        }
    }
    return res;
}


bool desc_ip_sort(Ip & first, Ip & second);

std::vector<Ip> filter_any(std::vector<Ip> filter_list, int val);


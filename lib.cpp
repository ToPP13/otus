#include "lib.h"
#include "version.h"
#include <algorithm>    // std::copy_if

int version()
{
    return PROJECT_VERSION_PATCH;
}


void print_ip_pool(std::vector<Ip> ip_pool)
{
    for(auto ip : ip_pool)
    {
        ip.print();
        std::cout << std::endl;
    }
}

bool Ip::operator == (const Ip &Ref) const
{
    return(components == Ref.components);
}

void Ip::print()
{
    for(auto ip_part = components.cbegin(); ip_part != components.cend(); ++ip_part)
    {
        if (ip_part != components.cbegin())
        {
            std::cout << ".";
        }
        std::cout << *ip_part;
    }
}

// a < b - > (a,b) - ascending order
// a < b - > (b,a) - descending order
// compare fun for vector of one type but different size
bool desc_ip_sort(Ip & first,Ip & second)
{
    uint min_size = std::min(first.components.size(), second.components.size());
    // compare while same size
    for(uint i = 0;i < min_size; i++)
    {
        if (first.components.at(i) != second.components.at(i))
            return first.components.at(i) > second.components.at(i);
    }
    // descending order, so if size of vectors are equal or first is less, it comes later
    if (second.components.size() < first.components.size())
        return false;
    return true;
}

std::vector<Ip> filter(std::vector<Ip> filter_list)
{
    std::vector<Ip> res;
    std::copy(filter_list.begin(), filter_list.end(), std::back_inserter(res));
    return res;
}

std::vector<Ip> filter_any(std::vector<Ip> filter_list, int val)
{
    std::vector<Ip> res;
    for(auto ip : filter_list)
    {
        if (std::find(ip.components.begin(), ip.components.end(), val) != ip.components.end())
            res.push_back(ip);
    }
    return res;
}


// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
std::vector<std::string> split(const std::string &str, char d)
{
    std::vector<std::string> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}



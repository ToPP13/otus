#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]

using std::cout;
using std::endl;
using std::string;
using std::vector;

auto split(const std::string &str, char d)
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


//// vector<string>
//template<typename T>
//bool asc_ip_sort (T first,T second)
//{
//    auto first_it = first.cbegin();
//    auto second_it = second.cbegin();
//    while(first_it != first.cend() && second_it != second.cend())
////    for (auto iterators = std::make_tuple(first.cbegin(),second.cbegin(),
////                                          std::get<0>(t) != first.cend(), std::get<1>(t) != second.cend();
////                                          std::get<0>(t)++, std::get<1>(t);)
////        if (*first_it == *second_it)
////            continue;
//    for(;first_it != first.cend() && second_it != second.cend;++first_it,++second_it)
//        if (*std::get<0>(t) == *std::get<1>(t))
//            continue;
//        return *std::get<0>(t) > *std::get<1>(t);
//    if (second_it == second.cend())
//        return true;
//    if (first_it == first.cend())
//        return false;
//    return true;
//}


bool desc_string_sort(string first, string second)
{
    auto min_len = std::min(first.size(), second.size());
    for(uint i = 0; i < min_len; ++i)
    {
        if (first[i] == second[i])
            continue;
        return first[i] < second[i];
    }
    if (first.size() <= second.size())
        return true;
    return false;
}

//template<typename T>
//bool desc_ip_sort(T first,T second)
//template<typename T>
//bool desc_ip_sort(vector<string> first,vector<string> second)
//template<typename T>
//bool desc_ip_sort(T first,T second)
bool desc_ip_sort(vector<string> first,vector<string> second)
{
    auto first_it = first.cbegin();
    auto second_it = second.cbegin();
    for(;first_it != first.cend() && second_it != second.cend();++first_it,++second_it)
    {
        if (*first_it == *second_it)
            continue;
        else
            return desc_string_sort(*first_it, *second_it);
//        return (*first_it) > (*second_it);
//        return stoi(*first_it) > stoi(*second_it);
//        return atoi(first_it->c_str()) < atoi(second_it->c_str());
    }
    if (second_it == second.cend())
        return false;
//    if (first_it == first.cend())
//        return true;
    return true;
}


void print_ip(std::vector<std::vector<std::string> > ip_pool)
{
    for(auto ip = ip_pool.cbegin(); ip != ip_pool.cend(); ++ip)
    {
        for(auto ip_part = ip->cbegin(); ip_part != ip->cend(); ++ip_part)
        {
            if (ip_part != ip->cbegin())
            {
                std::cout << ".";

            }
            std::cout << *ip_part;
        }
        std::cout << std::endl;
    }
}

//int main(int argc, char const *argv[])
int main()
{
//    if (argc != 2)
//    {
//        std::string standart_error = "Incorrect amount of arguments. ";
//        if (argc > 2)
//            std::cout << standart_error + "Need only one source" << std::endl;
//        if (argc < 2)
//            std::cout << standart_error + "No source" << std::endl;
//        exit(1);
//    }

//    const std::string source = argv[1];
//    std::ifstream inFile;
//    inFile.open(source);
//    if (!inFile) {
//        std::cout << "Unable to open file" << std::endl;
//        exit(2); // terminate with error
//    }

    cout << "Hello!" << endl;
    try
    {
        std::vector<std::vector<std::string> > ip_pool;

        for(std::string line; std::getline(std::cin, line);)
        {
            std::vector<std::string> ip_as_string = split(line, '\t');
            ip_pool.push_back(split(ip_as_string.at(0), '.'));
        }

        // TODO reverse lexicographically sort

        vector<string> ex1{"1", "1"};
        vector<string> ex3{"1", "2"};
        vector<string> ex4{"1", "0"};
        auto res3 = desc_ip_sort(ex1, ex3);
        auto res4 = desc_ip_sort(ex1, ex4);
        cout << res3 << endl;
        cout << res4 << endl;

        print_ip(ip_pool);
        std::sort(ip_pool.begin(), ip_pool.end(), desc_ip_sort);
        print_ip(ip_pool);


        // 222.173.235.246
        // 222.130.177.64
        // 222.82.198.61
        // ...
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first byte and output
        // ip = filter(1)

        // 1.231.69.33
        // 1.87.203.225
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first and second bytes and output
        // ip = filter(46, 70)

        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76

        // TODO filter by any byte and output
        // ip = filter_any(46)

        // 186.204.34.46
        // 186.46.222.194
        // 185.46.87.231
        // 185.46.86.132
        // 185.46.86.131
        // 185.46.86.131
        // 185.46.86.22
        // 185.46.85.204
        // 185.46.85.78
        // 68.46.218.208
        // 46.251.197.23
        // 46.223.254.56
        // 46.223.254.56
        // 46.182.19.219
        // 46.161.63.66
        // 46.161.61.51
        // 46.161.60.92
        // 46.161.60.35
        // 46.161.58.202
        // 46.161.56.241
        // 46.161.56.203
        // 46.161.56.174
        // 46.161.56.106
        // 46.161.56.106
        // 46.101.163.119
        // 46.101.127.145
        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76
        // 46.55.46.98
        // 46.49.43.85
        // 39.46.86.85
        // 5.189.203.46
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}

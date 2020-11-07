#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include "lib.h"


auto read_ip_pool()
{
    std::vector<Ip> ip_pool;
    try
    {
        for(std::string line; std::getline(std::cin, line);)
        {
            auto file_line = split(line, '\t');
            auto ip_string_components = split(file_line.at(0), '.');
            std::vector<int> ip_components;
            try
            {
                ip_string_components.reserve(ip_string_components.size());
                for (auto ip_string_component : ip_string_components)
                    ip_components.push_back(stoi(ip_string_component));
                ip_pool.push_back(Ip(ip_components));
            }
            catch (const std::invalid_argument& ia)
            {
                  std::cerr << "Invalid argument: " << ia.what() << '\n';
            }
            catch (const std::out_of_range& ia)
            {
                  std::cerr << "Invalid argument: " << ia.what() << '\n';
            }
        }

    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
    return ip_pool;
}


int main()
{
    std::vector<Ip> ip_pool = read_ip_pool();

    std::sort(ip_pool.begin(), ip_pool.end(), desc_ip_sort);
    print_ip_pool(ip_pool);

    auto filtered1 = filter(ip_pool, 1);
    print_ip_pool(filtered1);

    auto filtered2 = filter(ip_pool, 46, 70);
    print_ip_pool(filtered2);

    auto filtered3 = filter_any(ip_pool, 46);
    print_ip_pool(filtered3);
    //24e7a7b2270daee89c64d3ca5fb3da1a


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

    return 0;
}

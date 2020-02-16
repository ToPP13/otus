#include <string>
#include <vector>
#include <iostream>
#include <gtest/gtest.h>
#include "lib.h"

TEST(gtest_version, gtest_version_basic)
{
    ASSERT_GT(version(), 0);
}

TEST(gtest_split, gtest_split_basic)
{
    std::vector<std::string> res = {"1.1", "1"};
    std::vector<std::string> res2 = {"1", "1"};
    ASSERT_EQ(split("1.1 1", ' '), res);
    ASSERT_EQ(split("1.1", '.'), res2);
}

TEST(gtest_sort, gtest_sort_basic)
{
    std::vector<int> ip1_v {1, 1, 234, 8};
    std::vector<int> ip2_v {222, 173, 235, 246};
    std::vector<int> ip3_v {5, 157, 34, 251};
    Ip ip1(ip1_v);
    Ip ip2(ip2_v);
    Ip ip3(ip3_v);

    std::vector<Ip> to_sort = {ip1, ip2, ip3};
    std::vector<Ip> sorted = {ip2, ip3, ip1};
    std::sort(to_sort.begin(), to_sort.end(), desc_ip_sort);
    ASSERT_EQ(to_sort, sorted);
}

TEST(gtest_val_filter, gtest_val_filter_basic)
{
    std::vector<int> ip1_v {1, 1, 234, 8};
    std::vector<int> ip2_v {222, 173, 235, 246};
    std::vector<int> ip3_v {222, 157, 34, 251};
    Ip ip1(ip1_v);
    Ip ip2(ip2_v);
    Ip ip3(ip3_v);
    std::vector<Ip> to_sort = {ip1, ip2, ip3};

    auto filtered = filter(to_sort, 222);
    std::vector<Ip> res = {ip2, ip3};
    ASSERT_EQ(filtered, res);
}

TEST(gtest_two_val_filter, gtest_two_val_filter_basic)
{
    std::vector<int> ip1_v {1, 1, 234, 8};
    std::vector<int> ip2_v {222, 173, 235, 246};
    std::vector<int> ip3_v {222, 157, 34, 251};
    Ip ip1(ip1_v);
    Ip ip2(ip2_v);
    Ip ip3(ip3_v);

    std::vector<Ip> to_filter = {ip1, ip2, ip3};
    auto filtered1 = filter(to_filter, 222, 173);
    auto filtered2 = filter(to_filter, 222, 157);
    std::vector<Ip> res1 = {ip2};
    std::vector<Ip> res2 = {ip3};
    ASSERT_EQ(filtered1, res1);
    ASSERT_EQ(filtered2, res2);
}

TEST(gtest_any_val_filter, gtest_any_val_filter_basic)
{
    std::vector<int> ip1_v {1, 1, 234, 9};
    std::vector<int> ip2_v {222, 173, 9, 246};
    std::vector<int> ip3_v {222, 9, 34, 251};
    Ip ip1(ip1_v);
    Ip ip2(ip2_v);
    Ip ip3(ip3_v);

    std::vector<Ip> to_sort = {ip1, ip2, ip3};
    auto filtered1 = filter_any(to_sort, 1);
    auto filtered2 = filter_any(to_sort, 222);
    auto filtered3 = filter_any(to_sort, 9);

    std::vector<Ip> res1 = {ip1};
    std::vector<Ip> res2 = {ip2, ip3};
    std::vector<Ip> res3 = {ip1, ip2, ip3};

    std::cout << filtered1.size() << std::endl;
    ASSERT_EQ(filtered1, res1);
    ASSERT_EQ(filtered2, res2);
    ASSERT_EQ(filtered3, res3);
}


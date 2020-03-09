#include <algorithm>
#include <string>
#include <vector>
#include <iostream>
#include <gtest/gtest.h>
#include "lib.h"
#include "stdexcept"

TEST(gtest_version, gtest_version_basic)
{
    ASSERT_GT(version(), 0);
}


//TEST(gtest_custom_allocator, gtest_custom_allocator_basic)
//{
//    fixsize_logging_allocator<int, total> a;
//    for (int i = 0; i < total; ++i)
//        ASSERT_NO_THROW(a.allocate(1););
//    ASSERT_THROW(a.allocate(1), std::bad_alloc);
//}


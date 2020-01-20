////#define BOOST_TEST_MODULE test_version

#include "lib.h"

#include <gtest/gtest.h>

TEST(gtest_version, gtest_version_basic)
{
    ASSERT_GT(version(), 0);
//    ASSERT_GT(1, 0);
}


#define BOOST_TEST_MODULE test_version

#include "lib.h"

#include <boost/test/unit_test.hpp>
//#include <gtest/gtest.h>

BOOST_AUTO_TEST_SUITE(test_version)

BOOST_AUTO_TEST_CASE(test_valid_version)
{
    BOOST_CHECK(version() > 0);
}

}
//}
//TEST("TestVersion", "TestVersionBasic")
//TEST(test_version, test_version_basic)
//{
//    ASSERT_GT(version(), 0);
//    ASSERT_GT(1, 0);
//}


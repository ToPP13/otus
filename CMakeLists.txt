cmake_minimum_required(VERSION 3.2)

if (DEFINED ENV{TRAVIS_BUILD_NUMBER})
    project(hello_world VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else ()
    project(hello_world VERSION 0.0.1)
endif ()

find_package(Boost COMPONENTS unit_test_framework REQUIRED)
#find_package(gtest REQUIRED)
#enable_testing()
#find_package(GTest REQUIRED)
#include_directories(${GTEST_INCLUDE_DIR})
################################
# GTest
################################
#ADD_SUBDIRECTORY (gtest-1.6.0)
#enable_testing()
#include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include(GoogleTest)

configure_file(version.h.in version.h)

add_executable(hello_world_cli main.cpp)
add_library(hello_world lib.cpp)
add_executable(test_version test_version.cpp)


set_target_properties(hello_world_cli hello_world test_version PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)
target_include_directories(hello_world
    PRIVATE "${CMAKE_BINARY_DIR}"
)
set_target_properties(test_version PROPERTIES
    COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
    INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
)

target_link_libraries(hello_world_cli PRIVATE
    hello_world
)
target_link_libraries(test_version
    ${Boost_LIBRARIES}
    hello_world
)

if (MSVC)
    target_compile_options(hello_world_cli PRIVATE
        /W4
    )
    target_compile_options(hello_world PRIVATE
        /W4
    )
    target_compile_options(test_version PRIVATE
        /W4
    )
else ()
    target_compile_options(hello_world_cli PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(hello_world PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(test_version PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()



install(TARGETS hello_world_cli RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT martynovich@protei.ru)

include(CPack)

enable_testing()

add_test(test_version test_version)

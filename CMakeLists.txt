cmake_minimum_required(VERSION 3.2)


if (DEFINED ENV{TRAVIS_BUILD_NUMBER})
    # Set the name of the project.
    project(hello_world VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else ()
    # Set the name of the project.
    project(hello_world VERSION 0.0.1)
endif ()

# Load settings for an external project.
find_package(Boost COMPONENTS unit_test_framework REQUIRED)
#find_library(gtest.a )
find_package(GTest REQUIRED)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# Copy a file to another location and modify its contents.
configure_file(version.h.in version.h)

# Add an executable to the project using the specified source files.
add_executable(hello_world_cli main.cpp)

# Add a library to the project using the specified source files.
add_library(hello_world lib.cpp)
find_package (Threads)

add_executable(test_version test_version.cpp)
add_executable(gtest_version gtest_version.cpp)


# Set propertiess to a target.
#set_target_properties(hello_world_cli hello_world test_version PROPERTIES
set_target_properties(hello_world_cli hello_world test_version gtest_version PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

# Add include directories to a target.
# CMAKE_BINARY_DIR - The path to the top level of the build tree.
target_include_directories(hello_world
    PRIVATE "${CMAKE_BINARY_DIR}"
)

# CMAKE_CURRENT_BINARY_DIR - The path to the binary directory currently being processed.
include_directories(${CMAKE_CURRENT_BINARY_DIR})

# Add include directories to the build.
include_directories(${GTEST_INCLUDE_DIR})

set_target_properties(test_version PROPERTIES
    COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
    INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
)

set_target_properties(gtest_version PROPERTIES
    INCLUDE_DIRECTORIES ${GTEST_INCLUDE_DIRS}
)

target_link_libraries(hello_world_cli PRIVATE hello_world)
target_link_libraries(test_version ${Boost_LIBRARIES} hello_world)
target_link_libraries(gtest_version ${GTEST_LIBRARIES} hello_world ${GTEST_MAIN_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

# Add compile options to a target.
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
    target_compile_options(gtest_version PRIVATE
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
    target_compile_options(gtest_version PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()



# Load and run CMake code from a file or module.
install(TARGETS hello_world_cli RUNTIME DESTINATION bin)

# Set a CMake, cache or environment variable to a given value.
set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT martynovich@protei.ru)

include(CPack)

# Enable testing for current directory and below.
enable_testing()

# Add a test to the project to be run by ctest(1).
add_test(test_version test_version)
add_test(gtest_version gtest_version)

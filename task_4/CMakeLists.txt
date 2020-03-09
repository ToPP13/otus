cmake_minimum_required(VERSION 3.2)


if (DEFINED ENV{TRAVIS_BUILD_NUMBER})
    project(doxygen VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else ()
    project(doxygen VERSION 0.0.1)
endif ()

# Load settings for an external project.
find_package (GTest REQUIRED)
find_package (Threads REQUIRED)


# Copy a file to another location and modify its contents.
configure_file(version.h.in version.h)

# Add an executable to the project using the specified source files.
add_executable(doxygen_cli doxygen.cpp)

# Add a library to the project using the specified source files.
add_library(doxygen lib.cpp)

add_executable(gtest gtest.cpp)


# Set propertiess to a target.
set_target_properties(doxygen_cli doxygen gtest PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

# Add include directories to a target.
# CMAKE_BINARY_DIR - The path to the top level of the build tree.
target_include_directories(doxygen PRIVATE "${CMAKE_BINARY_DIR}" )

# Add include directories to the build.
include_directories(${GTEST_INCLUDE_DIR})
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set_target_properties(gtest PROPERTIES
    INCLUDE_DIRECTORIES ${GTEST_INCLUDE_DIRS}
)

target_link_libraries(doxygen_cli PRIVATE doxygen)
target_link_libraries(gtest ${GTEST_LIBRARIES} doxygen ${GTEST_MAIN_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

# Add compile options to a target.
if (MSVC)
    target_compile_options(doxygen_cli PRIVATE
        /W4
    )
    target_compile_options(doxygen PRIVATE
        /W4
    )
    target_compile_options(gtest PRIVATE
        /W4
    )
else ()    
    target_compile_options(doxygen_cli PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(doxygen PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(gtest PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()



# Load and run CMake code from a file or module.
install(TARGETS doxygen_cli RUNTIME DESTINATION bin)

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
add_test(gtest gtest)


cmake_minimum_required(VERSION 3.28)
project(function-test)

set(CMAKE_CXX_STANDARD 20)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wformat=2 -Wconversion -Wimplicit-fallthrough")

    #elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
endif()

include(FetchContent)

# Setup Asio
# Based on cmake file provided by havogt:
# https://stackoverflow.com/questions/65586352/is-it-possible-to-use-fetchcontent-or-an-equivalent-to-add-a-library-that-has-no

FetchContent_Declare(asio
        GIT_REPOSITORY https://github.com/chriskohlhoff/asio.git
        GIT_TAG master
        CONFIGURE_COMMAND ""
        BUILD_COMMAND ""
)

FetchContent_GetProperties(asio)
if(NOT asio_POPULATED)
    FetchContent_Populate(asio)
endif()

add_library(asio INTERFACE)
target_include_directories(asio INTERFACE ${asio_SOURCE_DIR}/asio/include)
find_package(Threads)
target_link_libraries(asio INTERFACE Threads::Threads)

# Own application

add_executable(function-test
        src/main.cpp
        src/main.cpp)
#target_include_directories(function-test PRIVATE )
target_link_libraries(function-test PRIVATE asio)

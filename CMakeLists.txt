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

set(CROW_USE_BOOST 0)
set(CROW_AMALGAMATE 0)
set(CROW_BUILD_TESTS 0)

FetchContent_Declare(crow
        GIT_REPOSITORY https://github.com/CrowCpp/Crow.git
        GIT_TAG master
        CONFIGURE_COMMAND ""
        BUILD_COMMAND ""
)

FetchContent_GetProperties(crow)
if(NOT crow_POPULATED)
    FetchContent_Populate(crow)
endif()

# We use Crow's cmake module to find the asio installed on the local system,
# this is because Crow does not seem to play nicely with an asio from fetch_content
list(APPEND CMAKE_MODULE_PATH ${crow_SOURCE_DIR}/cmake)
find_package(asio REQUIRED)


add_library(crow INTERFACE)
target_include_directories(crow INTERFACE ${crow_SOURCE_DIR}/include)
target_link_libraries(crow INTERFACE asio::asio Threads::Threads)



# Own application

add_executable(function-test
        src/main.cpp
        src/main.cpp)

target_compile_definitions(function-test INTERFACE USE_STANDALONE_ASIO)
#target_compile_definitions(function-test INTERFACE ASIO_NO_TS_EXECUTORS)

#target_include_directories(function-test PRIVATE )
target_link_libraries(function-test PRIVATE asio::asio crow)

add_custom_command(
        TARGET function-test POST_BUILD
        COMMAND cp
        ${CMAKE_SOURCE_DIR}/local.settings.json
        ${CMAKE_CURRENT_BINARY_DIR}/local.settings.json)

add_custom_command(
        TARGET function-test POST_BUILD
        COMMAND cp
        ${CMAKE_SOURCE_DIR}/host.json
        ${CMAKE_CURRENT_BINARY_DIR}/host.json)

add_custom_command(
        TARGET function-test POST_BUILD
        COMMAND cp
        ${CMAKE_SOURCE_DIR}/simple-http-trigger/function.json
        ${CMAKE_CURRENT_BINARY_DIR}/simple-http-trigger/function.json)
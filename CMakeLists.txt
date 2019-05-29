cmake_minimum_required(VERSION 2.8.7)
set(PROJECT_NAME_STR pandora)
project(${PROJECT_NAME_STR})

find_package(Threads REQUIRED)

# make sure that we have support for C++11
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++17" COMPILER_SUPPORTS_CXX17)
CHECK_CXX_COMPILER_FLAG("-std=c++14" COMPILER_SUPPORTS_CXX14)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)

if(COMPILER_SUPPORTS_CXX17)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage -std=c++17")
elseif(COMPILER_SUPPORTS_CXX14)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage -std=c++14")
elseif(COMPILER_SUPPORTS_CXX11)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage -std=c++0x")
else()
        message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

#-------------------
# Module source
#-------------------
set(PROJECT_LIB_NAME ${PROJECT_NAME_STR}_impl)
set(SOURCE_DIR ${PROJECT_SOURCE_DIR}/src/module/)
set(API_DIR ${PROJECT_SOURCE_DIR}/src/module/api/)
include_directories(${SOURCE_DIR})
include_directories(${API_DIR})
include_directories(${PROJECT_SOURCE_DIR}/test/dummy/)

file(GLOB SRC_FILES 
    ${SOURCE_DIR}/*.cpp
    ${API_DIR}/Display.cpp
    ${PROJECT_SOURCE_DIR}/str/apps/test/dummy/Contoroller.cpp
    )
add_library(${PROJECT_LIB_NAME} ${SRC_FILES})

#-------------------
# set common include folder for module
#-------------------

#-------------------
# Test
#-------------------
enable_testing()
find_package(GTest REQUIRED)

set(PROJECT_TEST_NAME ${PROJECT_NAME_STR}_test)
include_directories(${GTEST_INCLUDE_DIRS} ${SOURCE_DIR})
include_directories(${GTEST_INCLUDE_DIRS} ${API_DIR})

file(GLOB TEST_SRC_FILES ${PROJECT_SOURCE_DIR}/test/*.cpp)
add_executable(${PROJECT_TEST_NAME} ${TEST_SRC_FILES} ${SRC_FILES})
#add_dependencies(${PROJECT_TEST_NAME} googletest)

target_link_libraries(${PROJECT_TEST_NAME} GTest::GTest GTest::Main ${CMAKE_THREAD_LIBS_INIT})

add_test(test1 ${PROJECT_TEST_NAME})

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

if (CMAKE_BUILD_TYPE STREQUAL "Coverage")
    include(CodeCoverage)
    setup_target_for_coverage(test_coverage ${PROJECT_TEST_NAME} coverage)

    SET(CMAKE_CXX_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage")
    SET(CMAKE_C_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage")
endif() #CMAKE_BUILD_TYPE STREQUAL "Coverage"
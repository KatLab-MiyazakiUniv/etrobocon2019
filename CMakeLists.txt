cmake_minimum_required(VERSION 2.8.7)
set(PROJECT_NAME_STR pandora)
project(${PROJECT_NAME_STR} C CXX)

find_package(Threads REQUIRED)

# make sure that we have support for C++11
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++17" COMPILER_SUPPORTS_CXX17)
CHECK_CXX_COMPILER_FLAG("-std=c++14" COMPILER_SUPPORTS_CXX14)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)

if(COMPILER_SUPPORTS_CXX17)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage -std=c++17")
if(COMPILER_SUPPORTS_CXX14)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage -std=c++14")
if(COMPILER_SUPPORTS_CXX11)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage -std=c++0x")
else()
        message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

if(CMAKE_COMPILER_IS_GNUCXX)
    add_definitions(-Wall -ansi -Wno-deprecated -pthread -std=c++11)
endif()


#-------------------
# set common include folder for module
#-------------------
set(COMMON_INCLUDES ${PROJECT_SOURCE_DIR}/str/apps/include)
set(EXPLORER_INCLUDES ${PROJECT_SOURCE_DIR}/str/apps/explorer)
set(EXT_PROJECTS_DIR ${PROJECT_SOURCE_DIR}/str/apps/ext)

#-------------------
# Module source
#-------------------
set(PROJECT_LIB_NAME ${PROJECT_NAME_STR}_impl)
set(SOURCE_DIR ${PROJECT_SOURCE_DIR}/str/apps/src)
set(EXPLORER_DIR ${PROJECT_SOURCE_DIR}/str/apps/explorer)

include_directories(${COMMON_INCLUDES})
include_directories(${EXPLORER_INCLUDES})
file(GLOB SRC_FILES ${SOURCE_DIR}/Pid.cpp
    ${SOURCE_DIR}/SpeedControl.cpp
    ${SOURCE_DIR}/TurnControl.cpp
    ${SOURCE_DIR}/LineTracerWalker.cpp
    ${SOURCE_DIR}/NormalCourse.cpp
    ${SOURCE_DIR}/LeftNormalCourse.cpp
    ${SOURCE_DIR}/RightNormalCourse.cpp
    ${SOURCE_DIR}/FirstCode.cpp
    ${SOURCE_DIR}/Walker.cpp
    ${SOURCE_DIR}/RightCourse.cpp
    ${SOURCE_DIR}/LeftCourse.cpp
    ${SOURCE_DIR}/EtRobocon2018.cpp
    ${SOURCE_DIR}/UserInterface.cpp
    ${SOURCE_DIR}/Lifter.cpp
    ${SOURCE_DIR}/Distinguisher.cpp
    ${SOURCE_DIR}/BasicWalker.cpp
    ${SOURCE_DIR}/Parking.cpp
    ${SOURCE_DIR}/BlockArea.cpp
    ${SOURCE_DIR}/BlockStrategy.cpp
    ${SOURCE_DIR}/InitialPositionCodeDecoder.cpp
    ${SOURCE_DIR}/Selector.cpp
    ${SOURCE_DIR}/Explorer.cpp
    ${SOURCE_DIR}/Node.cpp
    ${SOURCE_DIR}/LPF.cpp
    ${SOURCE_DIR}/MotorAngle.cpp
    ${SOURCE_DIR}/WheelOdometry.cpp
    ${SOURCE_DIR}/Navigator.cpp
    ${SOURCE_DIR}/AIAnswer.cpp
    ${SOURCE_DIR}/BlockSolver.cpp
    )
add_library(${PROJECT_LIB_NAME} ${SRC_FILES})

add_subdirectory(${EXT_PROJECTS_DIR}/gtest)

#-------------------
# Test
#-------------------
add_definitions(${MSVC_COMPILER_DEFS})
enable_testing()
set(PROJECT_TEST_NAME ${PROJECT_NAME_STR}_test)
include_directories(${GTEST_INCLUDE_DIRS} ${COMMON_INCLUDES})

file(GLOB TEST_SRC_FILES ${PROJECT_SOURCE_DIR}/str/apps/test/*.cpp)
add_executable(${PROJECT_TEST_NAME} ${TEST_SRC_FILES} ${SRC_FILES})
add_dependencies(${PROJECT_TEST_NAME} googletest)


if(NOT WIN32 OR MINGW)
    target_link_libraries(${PROJECT_TEST_NAME}
        ${GTEST_LIBS_DIR}/libgtest.a
        ${GTEST_LIBS_DIR}/libgtest_main.a
        )
else()
    target_link_libraries(${PROJECT_TEST_NAME}
        debug ${GTEST_LIBS_DIR}/DebugLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest${CMAKE_FIND_LIBRARY_SUFFIXES}
        optimized ${GTEST_LIBS_DIR}/ReleaseLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest${CMAKE_FIND_LIBRARY_SUFFIXES}
        )
    target_link_libraries(${PROJECT_TEST_NAME}
        debug ${GTEST_LIBS_DIR}/DebugLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest_main${CMAKE_FIND_LIBRARY_SUFFIXES}
        optimized ${GTEST_LIBS_DIR}/ReleaseLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest_main${CMAKE_FIND_LIBRARY_SUFFIXES}
        )
endif()

target_link_libraries(${PROJECT_TEST_NAME} ${CMAKE_THREAD_LIBS_INIT})

add_test(test1 ${PROJECT_TEST_NAME})

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

if (CMAKE_BUILD_TYPE STREQUAL "Coverage")
    include(CodeCoverage)
    setup_target_for_coverage(test_coverage ${PROJECT_TEST_NAME} coverage)

    SET(CMAKE_CXX_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage")
    SET(CMAKE_C_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage")
endif() #CMAKE_BUILD_TYPE STREQUAL "Coverage"
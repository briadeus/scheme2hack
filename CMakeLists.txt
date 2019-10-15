cmake_minimum_required (VERSION 3.8)
set(CMAKE_CXX_STANDARD 11)

#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

#set(CXX_FLAGS "-Wall")
#set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

project(scheme2hack)

set(project_BIN ${PROJECT_NAME})


file(GLOB SOURCES src/*.cpp)


# Fügen Sie der ausführbaren Datei dieses Projekts eine Quelle hinzu.
add_executable (${project_BIN} ${SOURCES})


# GTest

#test
set(GTEST_ROOT "C:/dev/lib/googletest-master/googletest")
set(GTEST_LIBRARY "C:/dev/lib/googletest-master/out/build/x86-Debug/lib/gtestd.lib")
set(GTEST_MAIN_LIBRARY "C:/dev/lib/googletest-master/out/build/x86-Debug/lib/gtest_maind.lib")
set(GTEST_INCLUDE_DIRS "C:/dev/lib/googletest-master/googletest/include")


# enable dynamic linking in VS Studio
set( gtest_force_shared_crt ON CACHE BOOL "Always use msvcrt.dll" FORCE)

file(GLOB TEST_SOURCES test/*Test.cpp)

#find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Link runTests with what we want to test and the GTest library
add_executable(testRunner test/testRunner.cpp  ${TEST_SOURCES})
#d_executable(testRunner test/testRunner.cpp  test/scannerTest.cpp)
target_link_libraries(testRunner ${GTEST_MAIN_LIBRARY} ${GTEST_LIBRARY})


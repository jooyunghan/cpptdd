project(chapterFirstExample)
cmake_minimum_required(VERSION 2.6)

include_directories($ENV{GMOCK_HOME}/include $ENV{GMOCK_HOME}/gtest/include)
link_directories($ENV{GMOCK_HOME}/mybuild $ENV{GMOCK_HOME}/mybuild/gtest)
add_definitions(-DGTEST_USE_OWN_TR1_TUPLE=1)

set(sources 
   main.cpp 
   SoundexTest.cpp)

add_executable(test ${sources})
target_link_libraries(test pthread)
target_link_libraries(test gmock)
target_link_libraries(test gtest)



cmake_minimum_required(VERSION 3.19)
project(ex1)

set(CMAKE_CXX_STANDARD 11)

add_executable(ex1 testMain.cpp Group.cpp Node.cpp Player.cpp SearchTree.cpp PlayerManager.h
        library1.h library1.cpp)
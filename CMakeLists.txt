cmake_minimum_required(VERSION 3.19)
project(ex1)

set(CMAKE_CXX_STANDARD 11)

add_executable(ex1 main.cpp Classes/Group.cpp Classes/Node.cpp Classes/Player.cpp Classes/SearchTree.cpp Headers/PlayerManager.h
        main1.cpp)
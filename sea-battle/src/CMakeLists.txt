cmake_minimum_required(VERSION 3.23)
project(sea-battle)

set(CMAKE_CXX_STANDARD 23)

file(GLOB SOURCES
        skills/*.h
        skills/*.cpp
        base/*.h
        base/*.cpp
        interface/*.h
        interface/*.cpp
        interface/terminalInterface/*.h
        interface/terminalInterface/*.cpp
        )


add_executable(sea-battle ${SOURCES}
        main.cpp)

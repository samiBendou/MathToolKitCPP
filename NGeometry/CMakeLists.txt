cmake_minimum_required(VERSION 3.12)
project(NGeometry)

set(CMAKE_CXX_STANDARD 11)

add_library(NGeometry STATIC
        source/NSegment.cpp header/NSegment.h
        source/NCompact.cpp header/NCompact.h
        source/NDSet.cpp header/NDSet.h
        source/NParallelepiped.cpp header/NParallelepiped.h
        )
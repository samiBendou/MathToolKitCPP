cmake_minimum_required(VERSION 3.9)
project(NGeometry)

set(CMAKE_CXX_STANDARD 11)

include_directories(header)
include_directories(../NAlgebra/header)

add_library(NGeometry STATIC
        source/NSegment.cpp header/NSegment.h
        source/NCompact.cpp header/NCompact.h
        source/NDSet.cpp header/NDSet.h
        source/NParallelepiped.cpp header/NParallelepiped.h
        header/NGeometry.h)
cmake_minimum_required(VERSION 3.9)
project(NAnalysis)

set(CMAKE_CXX_STANDARD 11)

include_directories(header)
include_directories(../NAlgebra/header)
include_directories(../NGeometry/header)

add_library(NAnalysis STATIC
        source/NPField.cpp header/NPField.h
        source/NOde.cpp header/NOde.h
        source/NConstantField.cpp header/NConstantField.h
        source/SNewtonianField.cpp header/SNewtonianField.h
        )


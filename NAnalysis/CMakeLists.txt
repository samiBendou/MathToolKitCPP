cmake_minimum_required(VERSION 3.12)
project(NAnalysis)

set(CMAKE_CXX_STANDARD 11)

add_library(NAnalysis STATIC
        source/NPField.cpp header/NPField.h
        source/NOde.cpp header/NOde.h
        source/NConstantField.cpp header/NConstantField.h
        source/SNewtonianField.cpp header/SNewtonianField.h
        )


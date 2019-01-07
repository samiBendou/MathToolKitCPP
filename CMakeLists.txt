cmake_minimum_required(VERSION 3.9)
project(MathToolKitCPP)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(MathToolKit/NAlgebra)
add_subdirectory(MathToolKit/NAnalysis)
add_subdirectory(MathToolKit/NGeometry)

add_subdirectory(TestsMathToolKitCPP)

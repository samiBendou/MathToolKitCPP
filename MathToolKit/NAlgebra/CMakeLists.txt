cmake_minimum_required(VERSION 3.9)
project(NAlgebra)

set(CMAKE_CXX_STANDARD 11)

include_directories(header)

add_library(NAlgebra STATIC
        source/NVector.cpp header/NVector.h
        header/Vector3.h
        source/NPMatrix.cpp header/NPMatrix.h
        source/AESByte.cpp header/AESByte.h
        source/Pixel.cpp header/Pixel.h header/typedef.h
        header/NAlgebra.h)

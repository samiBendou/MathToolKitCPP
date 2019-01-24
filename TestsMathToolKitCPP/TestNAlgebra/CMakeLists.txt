set(TEST_SOURCES_NVECTOR TestNVector.cpp TestNVectorFuncOp.cpp TestVector3.cpp)
set(TEST_SOURCES_NPMATRIX TestNPMatrix.cpp TestNPMatrixFuncOp.cpp)
set(TEST_SOURCES_SCALAR TestPixel.cpp)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-g -O0 -Wall -Werror -Wextra -Wpedantic -Wconversion -Wswitch-default -Wswitch-enum -Wunreachable-code -Wwrite-strings -Wcast-align -Wshadow -Wundef -fprofile-arcs -ftest-coverage ${CMAKE_CXX_FLAGS}")
set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE 1)

cmake_policy(SET CMP0023 OLD) # Allow mixed target_link_library


include_directories(../../MathToolKit/NAlgebra/header)

SET(COVERAGE OFF CACHE BOOL "Coverage")

add_executable(TestNAlgebra ${TEST_SOURCES_NVECTOR} ${TEST_SOURCES_NPMATRIX} ${TEST_SOURCES_SCALAR})

target_link_libraries(TestNAlgebra gtest ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(TestNAlgebra NAlgebra)
target_link_libraries(TestNAlgebra INTERFACE --coverage)


#add_executable(BenchNVector BenchNVector.cpp)

#target_link_libraries(BenchNVector gtest gtest_main)
#target_link_libraries(BenchNVector NAlgebra)

#add_executable(BenchNPMatrix BenchNPMatrix.cpp)

#target_link_libraries(BenchNPMatrix gtest gtest_main)
#target_link_libraries(BenchNPMatrix NAlgebra)

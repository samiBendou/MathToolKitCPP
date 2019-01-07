if (APPLE)
    add_definitions(-DGTEST_USE_OWN_TR1_TUPLE)
    add_definitions(-D__GLIBCXX__)
endif (APPLE)

cmake_policy(SET CMP0023 OLD) # Allow mixed target_link_library

set(MATHTOOLKIT_HEADER_PATHS ../../MathToolKit/NAlgebra/header ../../MathToolKit/NAnalysis/header ../../MathToolKit/NGeometry/header)
set(TEST_SOURCES_NVECTOR TestNVector.cpp TestNVectorFuncOp.cpp TestVector3.cpp)
set(TEST_SOURCES_NPMATRIX TestNPMatrix.cpp TestNPMatrixFuncOp.cpp)
set(TEST_SOURCES_SCALAR TestPixel.cpp)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(${MATHTOOLKIT_HEADER_PATHS})

SET(COVERAGE OFF CACHE BOOL "Coverage")

add_executable(TestNAlgebra ${TEST_SOURCES_NVECTOR} ${TEST_SOURCES_NPMATRIX} ${TEST_SOURCES_SCALAR} TestPixel.cpp)

#add_executable(TestNVector ${TEST_SOURCES_NVECTOR})
#add_executable(TestNPMatrix ${TEST_SOURCES_NPMATRIX})
#add_executable(TestScalarTypes ${TEST_SOURCES_SCALAR})
#add_executable(BenchNVector BenchNVector.cpp)
#add_executable(BenchNPMatrix BenchNPMatrix.cpp)

target_link_libraries(TestNAlgebra gtest gtest_main)
target_link_libraries(TestNAlgebra NAlgebra)

if (COVERAGE)
    target_compile_options(TestNAlgebra PRIVATE --coverage)
    target_link_libraries(TestNAlgebra PRIVATE --coverage)
endif ()

target_compile_options(TestNAlgebra PRIVATE -std=c++11  -g -Wall -Werror -Wextra -Wpedantic -Wconversion -Wswitch-default -Wswitch-enum -Wunreachable-code -Wwrite-strings -Wcast-align -Wshadow -Wundef)

#target_link_libraries(TestNVector gtest gtest_main)
#target_link_libraries(TestNVector NAlgebra)
#
#target_link_libraries(TestNPMatrix gtest gtest_main)
#target_link_libraries(TestNPMatrix NAlgebra)
#
#target_link_libraries(TestScalarTypes gtest gtest_main)
#target_link_libraries(TestScalarTypes NAlgebra)
#
#target_link_libraries(BenchNVector gtest gtest_main)
#target_link_libraries(BenchNVector NAlgebra)
#
#target_link_libraries(BenchNPMatrix gtest gtest_main)
#target_link_libraries(BenchNPMatrix NAlgebra)


add_test(
        NAME
        UnitTestNAlgebra
        COMMAND
        TestNAlgebra
)

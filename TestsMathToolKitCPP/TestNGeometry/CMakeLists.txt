if (APPLE)
    add_definitions(-DGTEST_USE_OWN_TR1_TUPLE)
    add_definitions(-D__GLIBCXX__)
endif (APPLE)

set(MATHTOOLKIT_HEADER_PATHS ../../MathToolKit/NAlgebra/header ../../MathToolKit/NAnalysis/header ../../MathToolKit/NGeometry/header)

include_directories(${MATHTOOLKIT_HEADER_PATHS})

add_executable(TestNGeometry TestNParallelepiped.cpp)

target_link_libraries(TestNGeometry gtest gtest_main)
target_link_libraries(TestNGeometry NGeometry NAlgebra)
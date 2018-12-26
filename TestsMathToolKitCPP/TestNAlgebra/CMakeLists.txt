if (APPLE)
    add_definitions(-DGTEST_USE_OWN_TR1_TUPLE)
    add_definitions(-D__GLIBCXX__)
endif (APPLE)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(TestNAlgebra TestNVector.cpp TestNVectorFuncOp.cpp TestVector3.cpp TestNPMatrix.cpp TestNPMatrixFuncOp.cpp TestPixel.cpp)

target_link_libraries(TestNAlgebra gtest gtest_main)
target_link_libraries(TestNAlgebra NAlgebra)



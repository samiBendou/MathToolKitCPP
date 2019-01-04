if (APPLE)
    add_definitions(-DGTEST_USE_OWN_TR1_TUPLE)
    add_definitions(-D__GLIBCXX__)
endif (APPLE)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(TestNAlgebra TestNVector.cpp TestNVectorFuncOp.cpp TestVector3.cpp TestNPMatrix.cpp TestNPMatrixFuncOp.cpp TestPixel.cpp)

add_executable(TestNVector TestNVector.cpp TestNVectorFuncOp.cpp TestVector3.cpp)
add_executable(TestNPMatrix TestNPMatrix.cpp TestNPMatrixFuncOp.cpp)
add_executable(TestScalarTypes TestPixel.cpp)
add_executable(BenchNVector BenchNVector.cpp)
add_executable(BenchNPMatrix BenchNPMatrix.cpp)

target_link_libraries(TestNAlgebra gtest gtest_main)
target_link_libraries(TestNAlgebra NAlgebra)

target_link_libraries(TestNVector gtest gtest_main)
target_link_libraries(TestNVector NAlgebra)

target_link_libraries(TestNPMatrix gtest gtest_main)
target_link_libraries(TestNPMatrix NAlgebra)

target_link_libraries(TestScalarTypes gtest gtest_main)
target_link_libraries(TestScalarTypes NAlgebra)

target_link_libraries(BenchNVector gtest gtest_main)
target_link_libraries(BenchNVector NAlgebra)

target_link_libraries(BenchNPMatrix gtest gtest_main)
target_link_libraries(BenchNPMatrix NAlgebra)


add_test(
        NAME
        unit
        COMMAND
        ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/TestNAlgebra
)

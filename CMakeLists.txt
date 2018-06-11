cmake_minimum_required(VERSION 3.10)
project(MathToolKit)

set(CMAKE_CXX_STANDARD 11)

add_executable(MathToolKit main.cpp NAlgebra/NVector.cpp NAlgebra/NVector.h NAlgebra/ENVector.cpp NAlgebra/ENVector.h NAlgebra/Vector3.cpp NAlgebra/Vector3.h NAlgebra/NPMatrix.cpp NAlgebra/NPMatrix.h NAlgebra/NMatrix.cpp NAlgebra/NMatrix.h NAnalysis/NPField.cpp NAnalysis/NPField.h NGeometry/NSegment.cpp NGeometry/NSegment.h NGeometry/NSet.cpp NGeometry/NSet.h NGeometry/NCompact.cpp NGeometry/NCompact.h NGeometry/NParallelepiped.cpp NGeometry/NParallelepiped.h mainBis.cpp NGeometry/NDSet.cpp NGeometry/NDSet.h NAnalysis/NOde.cpp NAnalysis/NOde.h NAnalysis/NConstantField.cpp NAnalysis/NConstantField.h NAnalysis/SNewtonianField.cpp NAnalysis/SNewtonianField.h tests.cpp tests.h ConsoleMenu.cpp ConsoleMenu.h)
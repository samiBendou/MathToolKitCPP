cmake_minimum_required(VERSION 3.10)
project(MathToolKit)

set(CMAKE_CXX_STANDARD 11)

add_executable(MathToolKit main.cpp NAlgebra/source/NVector.cpp NAlgebra/header/NVector.h NAlgebra/source/ENVector.cpp NAlgebra/header/ENVector.h NAlgebra/source/Vector3.cpp NAlgebra/header/Vector3.h NAlgebra/source/NPMatrix.cpp NAlgebra/header/NPMatrix.h NAlgebra/source/NMatrix.cpp NAlgebra/header/NMatrix.h NAnalysis/source/NPField.cpp NAnalysis/header/NPField.h NGeometry/source/NSegment.cpp NGeometry/header/NSegment.h NGeometry/source/NSet.cpp NGeometry/header/NSet.h NGeometry/source/NCompact.cpp NGeometry/header/NCompact.h NGeometry/source/NParallelepiped.cpp NGeometry/header/NParallelepiped.h mainBis.cpp NGeometry/source/NDSet.cpp NGeometry/header/NDSet.h NAnalysis/source/NOde.cpp NAnalysis/header/NOde.h NAnalysis/source/NConstantField.cpp NAnalysis/header/NConstantField.h NAnalysis/source/SNewtonianField.cpp NAnalysis/header/SNewtonianField.h tests.cpp tests.h ConsoleMenu.cpp ConsoleMenu.h)
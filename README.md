# MathToolKitCPP

### Author : samiBendou

### Last Update : 08/10/2018

### Current Version : 0.5

MathToolKit is a linear algebra and differential equations solving framework in C++. It's a tool box to ease applied maths and physics in C++. It's the a framework to perform fast and efficient scientific calculation and AI.

## NAlgebra

#### Overview

- Classic linear algebra objects such as euclidean vectors or dense matrices (tensors coming soon).
- Java-like syntax
- Very large range of operations such as +, *, linear mapping, matrix inversions... look at TestNAlgebra directory to have an overview.


#### Features

##### NVector

N-dimensional euclidean vectors. Featuring algebraical operations (E, +, *), swaps, shifts and classic vectors generator such as ones, zeros...
  
##### NPMatrix

NxP matrices. Featuring algebraical operations such as matrix product, linear map, gauss jordan elimination. Setters & getters, swappers and classic matrix generators such as ones, zeros...
  
##### NMatrix

Featuring LU decomposition, classic matrix recognition & generation (lower, upper, diag, eye...), linear systems solving, matrix inversion and determinant, fast exponentiation...
  
##### Vector3

3D Space vectors. Featuring cross product, coordinate transforms and rotations.
  
 ### NAnalysis
 
 #### Overview
 
 Representing numerical vector fields in finite dimension vector space. WIP.
 
 ### NGeometry
 
 #### Overview
 
 Representing compact domains in N-dimension and mesh theses. WIP.
 
 ### Compatibility
 
 The framework is written in C++11. It's recommended to use CMake and g++ to compile sources. I had some issues with Cygwin and Mingwin... Project has been coded using CLion, it provides easy to handle unit testing with googletest and stock build configuration.
 
 ### Install
 
 - Make sure you have CMake version 3.12 at least;
 - Clone googletest : https://github.com/google/googletest;
 - Clone the project;
 - Put the googletest library at TestMathToolKit/lib/googletest where googletest is the root of the previously downloaded googletest;
 - Compile using CMake.

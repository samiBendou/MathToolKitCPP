# MathToolKitCPP

### Author : samiBendou

### Last Update : 11/10/2018

### Current Version : 1.0

MathToolKit is C++ maths framework. 
It provides libraries that ease N-dimensional scientific calculation and simulation.
Can be used in various domains such as applied maths, physics, economics... 
The framework can be used to produce quickly and easily efficient C++ code. 

- Linear algebra library (NAlgebra)

- Differential equations solving library (NAnalysis)

- Geometry library (NGeometry)

- Designed to ease dynamic system simulation

- High level syntax and functionality (numpy/Matlab like)

- Complete integration of STL

- Highly serializable as string or std::vector

- Unit tested with googletest

## NAlgebra

#### Overview

- Matrix and vector classes.

- Manipulators : shift, swap, ...

- Linear Algebra : +, *, linear mapping, inversion, ...

- Generators : eye, ones, diag, ...
  
 ### NAnalysis
 
 #### Overview
 
- Representing numerical vector fields.

- Easy ode solving.

- Create your own fields by overloading NPField class g(u) function.

- Calculate fields on compact numerical domains.
 
 ### NGeometry
 
 #### Overview
 
 - Representing compact numerical domains.
 
 - Create mesh of domains.
 
 ### Compatibility
 
 The framework is written in C++11. It's recommended to use CMake and g++ to compile sources. I had some issues with Cygwin and Mingwin... Project has been coded using CLion, it provides easy to handle unit testing with googletest and stock build configuration.
 
 ### Install
 
 - Make sure you have CMake version 3.12 at least;
 - Clone googletest : https://github.com/google/googletest;
 - Clone the project;
 - Put the googletest library at TestMathToolKit/lib/googletest where googletest is the root of the previously downloaded googletest;
 - Compile using CMake.

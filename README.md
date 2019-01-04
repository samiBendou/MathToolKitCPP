[![Build Status](https://travis-ci.org/samiBendou/MathToolKitCPP.svg?branch=master)](https://travis-ci.org/samiBendou/MathToolKitCPP/builds)

# MathToolKitCPP

### Author : samiBendou

### Last Update : 04/01/2019

### Current Version : 1.1.1 (WIP)

## Version log :

- 1.1.1 : Integrating travis.org CI tool
- 1.1.0 :   Adding cascade calls interface for NAlgebra (vect.shift().swap()). Simplifying code structure.
            Optimizing execution time by inlining.
- 1.0.1 : Adding unit testing for NGeometry and NAnalyis and attempt to create a unified data structure
for geometrical N-dimensional shapes. Minor fixes.
- 1.0.0 : First release.

## General overivew

MathToolKit is a C++ maths framework. It introduces common mathematical abstractions such as matrix, vector, numerical fields, ODE...

Designed to save time solving commons mathematical problems for engineering.
It provides a mixed style API that gives you flexibility.
The library uses both STL standardization and low level C++ to provide fast and efficient computing.
It's designed very lightweight in order to be embedded on microelectronic devices.
It's template based implementation to provide support for custom scalar types (pixel matrix, AES matrix...).


Featuring :

- Large range of abstractions from algebra to geometry

- High level syntax (numpy like...)

- Cascade calls (matrix.shift().fill(), ...)

### Introduction

MathToolKit contains multiples libraries providing API that ease N-dimensional scientific calculation and simulation.
It can be used in various domains such as cryptography, theoretical physics, finance...
It's though to produce efficient numeric calculation with an intuitive numpy like syntax. 

The documentation of the framework is currently contained in header files.

### Compatibility

- Written using C++11

- Using CMake 3.9.2

- Tested on local with : clang Apple LLVM version 9.1.0 (clang-902.0.39.2)

- Tested on travis with : clang 5.0.0

## NAlgebra

Linear algebra library providing vectors and matrix objects.

#### Overview

- Manipulators : shift, swap, ...

- Linear Algebra : +, *, mapping, inversion, pow, ...

- Generators : eye, ones, diag, ...
  
 ### NAnalysis
 
 Differential calculus library providing numerical vector fields representation and easy ode solving.
 
 #### Overview
 
- Mesh fields on various domains (see NGeometry)

- Solve differential equations using fields representation
 
 ### NGeometry
 
 Geometry library. Representing compact numerical domains such as parallelepiped, spheres...
 
 #### Overview
 
 - Represent operations between domains
 
 - Calculate domains volume, area...
  
 - Create mesh of domains.

 ### Install
 
- Clone the project on your computer or IDE

- Copy the directories of the libraries you want to import onto your project

cmake-build-debug 

### Run Unit Tests

The framework is unit tested with googletest. The framework doesn't yet have a code coverage evaluation
but NAlgebra tests has been written.

If you want to run unit tests you have to import googletest onto the cloned project.

- Clone MathToolKitCPP project

- Download googletest last version and put the googletest directory at MathToolKit/TestsMathToolKitCPP/lib/ : 

```commandline
git clone https://github.com/google/googletest ./TestsMathToolKitCPP/lib/
```


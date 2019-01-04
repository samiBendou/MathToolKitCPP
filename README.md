# MathToolKitCPP

### Author : samiBendou

### Last Update : 30/10/2018

### Current Version : 1.1.0 (WIP)

## Version log :

- 1.1.0 :   Adding cascade calls interface for NAlgebra (vect.shift().swap()). Simplifying code structure.
            Optimizing execution time by inlining.
- 1.0.1 : Adding unit testing for NGeometry and NAnalyis and attempt to create a unified data structure
for geometrical N-dimensional shapes. Minor fixes.
- 1.0.0 : First release.

## General overivew

MathToolKit is a C++ maths framework. 

It introduces common mathematical abstractions such as matrix, vector, fields...

It's designed to save time solving commons mathematical problems for engineering.

Featuring :

- High level syntax and operators

- Large range of operations

- Lightweight code

- Complete integration of STL

- Template based implementation

- Unit tested with googletest

### Introduction

MathToolKit contains multiples libraries providing API that ease N-dimensional scientific calculation and simulation.
It's though for produce efficient numeric calculation with an intuitive syntax. 
It can be used in various domains such as cryptography, theoretical physics, finance...

The documentation of the framework is currently contained in header files.

### Compatibility

- Written in C++11

- Using CMake 3.12

## NAlgebra

Linear algebra library providing vectors and matrix template classes.

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

If you want to run unit tests you have to import googletest onto the cloned project.

- Clone MathToolKitCPP project

- Download googletest last version and put the googletest directory at MathToolKit/TestsMathToolKitCPP/lib/ : 

```commandline
git clone https://github.com/google/googletest ./TestsMathToolKitCPP/lib/
```


# MathToolKitCPP

### Author : samiBendou

### Last Update : 30/10/2018

### Current Version : 1.0.1

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

Linear algebra library providing vectors and matrix classes.

#### Overview

- Matrix and vector classes.

- Manipulators : shift, swap, ...

- Linear Algebra : +, *, linear mapping, inversion, ...

- Generators : eye, ones, diag, ...
  
 ### NAnalysis
 
 Differential calculus library
 
 #### Overview
 
- Representing numerical vector fields.

- Easy ode solving.

- Create your own fields by overloading NPField class g(u) function.

- Calculate fields on compact numerical domains.
 
 ### NGeometry
 
 Geometry library.
 
 #### Overview
 
 - Representing compact numerical domains.
 
 - Create mesh of domains.
 

 ### Install
 
- Clone the project on your computer or IDE

- Copy the directories of the libraries you want to import onto your project

### Run Unit Tests

If you want to run unit tests you have to import googletest onto the cloned project.

- Clone the project

- Download googletest last version : https://github.com/google/googletest

- Create a directory named lib in TestMathToolKitCPP

- Copy googletest-master directory on lib directory

- Rename googletest-master googletest


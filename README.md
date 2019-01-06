[![Build Status](https://travis-ci.org/samiBendou/MathToolKitCPP.svg?branch=master)](https://travis-ci.org/samiBendou/MathToolKitCPP/builds)

# MathToolKitCPP



## General overivew

### Introduction

MathToolKit is a C++ maths framework. It introduces common mathematical abstractions such as matrix, vector, numerical fields, ODE...
Designed to save time solving commons mathematical problems for engineering.

It provides a mixed style API that gives you flexibility.
The library uses both STL standardization and low level C++ to provide efficient computing.
It's designed very lightweight in order to be embedded on microelectronic devices.
It's template based implementation to provide support for custom scalar types (pixel matrix, AES matrix...).

Featuring :

- Large range of abstractions from algebra to geometry

- High level syntax (numpy like...)

- Cascade calls `matrix.shift().fill()`, ...

The documentation of the framework is currently hosted at : https://samibendou.github.io/MathToolKitCPP/.

#### NAlgebra

Linear algebra library providing vectors and matrix objects : [Documentation](https://samibendou.github.io/MathToolKitCPP/group___n_algebra.html)

- Manipulators : `shift()`, `swap()`, ...

- Linear Algebra : `+`, `*`, `inv()`, `pow()`, ...

- Generators : `eye()`, `ones()`, `diag()`, ...
  
 #### NAnalysis
 
 Differential calculus library providing numerical vector fields representation and easy ode solving.
 
- Mesh fields on various domains (see NGeometry)

- Solve differential equations using fields representation
 
 #### NGeometry
 
 Geometry library. Representing compact numerical domains such as parallelepiped, spheres...
 
 - Represent operations between domains
 
 - Calculate domains volume, area...
  
 - Create mesh of domains.

## Getting Started

### Install
 
1. Clone the project

2. Copy the directories of the libraries you want to import onto your project. 
eg : import NAlgebra if you want to use NPMatrix.

### 

### Run Unit Tests

The framework is unit tested with googletest. The framework doesnt yet have a code coverage evaluation
but over 60 NAlgebra tests has been written.

If you want to run unit tests you have to import googletest onto the cloned project.

1. Clone MathToolKitCPP project

2. Download googletest last version and put the googletest directory at MathToolKit/TestsMathToolKitCPP/lib/ : 

```commandline
git clone https://github.com/google/googletest ./TestsMathToolKitCPP/lib/

```

### Additional information

#### Author : samiBendou

#### Last Update : 06/01/2019

#### Current Version : 1.1.1

#### Compatibility

- Written using C++11

- Using CMake 3.9.2

- Tested on local with : clang Apple LLVM version 9.1.0 (clang-902.0.39.2)

- Tested on travis with : clang 5.0.0

#### Version log :

- 1.1.1 :   minor fixes related to integration of CI tool and generating doc using doxygen.
- 1.1.0 :   Adding cascade calls interface for NAlgebra API (vect.shift().swap()). Simplifying code structure.
            Optimizing execution time.
- 1.0.1 :   Adding unit testing for NGeometry and NAnalyis and attempt to create a unified data structure
            for geometrical N-dimensional shapes. Minor fixes.
- 1.0.0 :   First release.


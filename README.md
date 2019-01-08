[![Build Status](https://travis-ci.org/samiBendou/MathToolKitCPP.svg?branch=master)](https://travis-ci.org/samiBendou/MathToolKitCPP/builds)
[![Coverage Status](https://coveralls.io/repos/github/samiBendou/MathToolKitCPP/badge.svg?branch=master)](https://coveralls.io/github/samiBendou/MathToolKitCPP?branch=master)

# MathToolKitCPP

#### Last Update : 08/01/2019

#### Current Version : 1.1.2

## General overview

### Introduction

MathToolKit is a C++ maths framework. It introduces common mathematical abstractions such as matrix, vector, numerical fields, ODE...
Designed to save time solving commons mathematical problems for engineering.

The library uses both .
It's designed 
It's template based implementation to provide .

- **High level** numpy like syntax

- **Efficient** computing thanks to a mix of STL standardization and low level C++

- **Large range** of abstractions and methods from algebra to geometry

- **Lightweight** enough to be embedded on various microelectronic devices

- **Customization** oriented template based implementation


Currently only NAlgebra library is fully tested and functional. Work in progress on other libraries.
The full documentation of the framework is hosted [here](https://samibendou.github.io/MathToolKitCPP/).

### Install
 
1. Clone the project

2. Copy the directories of the libraries you want to import onto your project. 
eg : import NAlgebra if you want to use NPMatrix.

3. Take a look at tutorials [here](https://samibendou.github.io/MathToolKitCPP/group___n_algebra.html).

### Run Unit Tests

If you want to run unit tests you have to import googletest onto the cloned project.

1. Clone MathToolKitCPP project

2. Download googletest last version and put the googletest directory at MathToolKit/TestsMathToolKitCPP/lib/ : 

```commandline
git clone https://github.com/google/googletest ./TestsMathToolKitCPP/lib/

```

### Additional information

#### Author : samiBendou

#### Version log :

- 1.1.2 :   Minor fixes for gcc8
- 1.1.1 :   minor fixes related to integration of CI tool and generating doc using doxygen.
- 1.1.0 :   Adding cascade calls interface for NAlgebra API (vect.shift().swap()). Simplifying code structure.
            Optimizing execution time.
- 1.0.1 :   Adding unit testing for NGeometry and NAnalyis and attempt to create a unified data structure
            for geometrical N-dimensional shapes. Minor fixes.
- 1.0.0 :   First release.


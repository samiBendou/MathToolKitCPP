#ifndef MATHTOOLKITCPP_NALGEBRA_H
#define MATHTOOLKITCPP_NALGEBRA_H

/**
 * @defgroup NAlgebra Linear Algebra
 * @copyright Dahoux Sami 2018 All rights reserved.
 * @brief Linear algebra library.
 * @details NAlgebra is a library designed to provide intuitive and efficient use of common
 * linear object such as matrix or vector.
 *
 *  - It covers a large range of operations
 *  - It offers a code structure that allows you customization by inheritance
 *  - It's designed using templates so you can use custom scalar types
 *
 *  @{
 *  @page NAlgebraTutoStart Introduction
 *
 *  This section is a small tutorial which introduces you to `NAlgebra` objects and shows the basic of `NAlgebra` module.
 *
 *  @section NVector
 *
 *  `NVector` objects are abstraction for mathematical vectors :
 *
 *  @code{.cpp}
 *  NVector<int> u{4, 3, -9, 9}; // initializes a vector using coordinates
 *  std::cout << u; // displays "(4, 3, -9, 9)"
 *  @endcode
 *
 *  You can use aliases `vec_t`, `vec_char_t`, ... to use common scalar types.
 *  Full documentation of `NVector` is available [here](https://samibendou.github.io/MathToolKitCPP/class_n_vector.html).
 *
 * @subsection AlgclOpVec Algebraical Operations
 *
 * Common element-wise algebraical operations are provided. Syntax is very similar to C++ primitive types :
 *
 * @code{.cpp}
 * vec_t u{4, 3, -9, 9}, v{1, 1, 1, 1};
 * u *= 2;
 * std::cout << u + v; //displays "(10, 8, -16, 20)"
 * @endcode
 *
 * @subsection AlgcEucldOp Norm Based Euclidean Operations
 *
 * Dot product is represented in `NAlgebra` and a set of operators are provided to calculate distance, norm, ...
 *
 * @code{.cpp}
 * vec_t u{1, 1, 1, 1};
 * std::cout << !u; \\ return the norm of u : 2
 * @endcode
 *
 * @subsection ManipVec Manipulators
 *
 * Common manipulators are provided such as `shift` or `swap`, eg. :
 *
 * @code{.cpp}
 * vec_t u{1, 2, 3};
 * u.swap(0, 1).shift(1); // u = (1, 3, 2)
 * @endcode
 *
 * @subsection StaticVec Static Generators
 *
 * Generators use a syntax similar to numpy. For example :
 *
 * @code{.cpp}
 * vec_t u{vec_t::ones(3)}; // u = (1, 1, 1)
 * @endcode
 *
 * @subsection FuncOp Function Operator
 *
 * Function operator is used to access and eventually modify sub-ranges of a vector.
 *
 * @code{.cpp}
 * vec_t u{1, 2, 3}
 * std::cout << u(0, 1); // displays "(1, 2)"
 * @endcode
 *
 * It can also be chained with other operations. For example :
 *
 * @code{.cpp}
 * u(0, 1).fill(6);
 * std::cout << u(0, 2) + v(4, 6);
 * @endcode
 * @}
 */

#include <NVector.h>
#include <NPMatrix.h>
#include <Vector3.h>
#include <Pixel.h>
#include <AESByte.h>
#include <thirdparty.h>
#include <typedef.h>


#endif //MATHTOOLKITCPP_NALGEBRA_H

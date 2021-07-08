//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup exponential
  //! @{
  //! @var pow
  //!
  //! @brief Callable object performing the computation of the pow operation.
  //!
  //! **Required header:** `#include <eve/function/pow.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the pow operation   |
  //! | `operator[]` | Construct a conditional version of current function object |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template< value T, value U > auto operator()( T x, U y ) const noexcept requires compatible< T, U >;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`, `y`:   [values](../../concepts.html#value).
  //!
  //! **Return value**
  //!
  //!Returns [element-wise](../../../glossary.html#value) \f$x^y\f$.
  //!
  //! The result type is the [compatibility result](../../concept.html#compatibility) of the two parameters.
  //! In paticular we have (IEC 60559):
  //!
  //!  * pow(+0, y), where y is a negative odd integer, returns \f$+\infty\f$
  //!  * pow(-0, y), where y is a negative odd integer, returns \f$-\infty\f$
  //!  * pow(\f$\pm0\f$, y), where y is negative, finite, and is an even integer or a non-integer, returns \f$+\infty\f$
  //!  * pow(\f$\pm0\f$, \f$-\infty\f$) returns \f$+\infty\f$
  //!  * pow(+0, y), where y is a positive odd integer, returns +0
  //!  * pow(-0, y), where y is a positive odd integer, returns -0
  //!  * pow(\f$\pm0\f$, y), where y is positive non-integer or a positive even integer, returns +0
  //!  * pow(-1,\f$\pm\infty\f$) returns 1
  //!  * pow(+1, y) returns 1 for any y, even when y is NaN
  //!  * pow(x, \f$\pm0\f$) returns 1 for any x, even when x is NaN
  //!  * pow(x, y) returns NaN if x is finite and less than 0 and y is finite and non-integer.
  //!  * pow(x, \f$-\infty\f$) returns \f$+\infty\f$ for any |x|<1
  //!  * pow(x, \f$-\infty\f$) returns +0 for any |x|>1
  //!  * pow(x, \f$+\infty\f$) returns +0 for any |x|<1
  //!  * pow(x, \f$+\infty\f$) returns \f$+\infty\f$ for any |x|>1
  //!  * pow(\f$-\infty\f$, y) returns -0 if y is a negative odd integer
  //!  * pow(\f$-\infty\f$, y) returns +0 if y is a negative non-integer or even integer
  //!  * pow(\f$-\infty\f$, y) returns \f$-\infty\f$ if y is a positive odd integer
  //!  * pow(\f$-\infty\f$, y) returns \f$+\infty\f$ if y is a positive non-integer or even integer
  //!  * pow(\f$+\infty\f$, y) returns +0 for any y less than 0
  //!  * pow(\f$+\infty\f$, y) returns \f$+\infty\f$ for any y greater than 0
  //!  *  except where specified above, if any argument is NaN, NaN is returned
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::pow
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `pow[cond](x, ...)` is equivalent to `if_else(cond,pow(x, ...),x)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  ====================================================================================================
  //!  * `diff`
  //!
  //!     **Required header:**  #include <eve/function/diff/pow.hpp>
  //!  
  //!     The expression `diff_1st(pow)(x,y)` and `diff_2nd(pow)(x,y)` computes the partial
  //!      derivatives of \f$f\f$, where \f$f\f$ is the function \f$(x,y) \rightarrow \ x^y\f$.
  //!
  //! #### Example
  //!
  //! [**See it live on Compiler Explorer**](https://godbolt.org/z/TODO)
  //!
  //! @include{lineno} doc/core/pow.cpp
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(pow_, pow);
}

#include <eve/module/real/math/function/regular/generic/pow.hpp>

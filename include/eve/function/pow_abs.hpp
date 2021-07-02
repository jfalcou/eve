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
  //! @var pow_abs
  //!
  //! **Required header:**
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  #include <eve/function/pow_abs.hpp>
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! <br/>Callable object performing the computation of the pow_abs operation.
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the pow_abs operation   |
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
  //!
  //!
  //! **Return value**
  //!
  //!Returns [element-wise](../../../glossary.html#value) $|x|^y$.
  //!
  //! The result type is the [compatibility result](../../concept.html#compatibility) of the two parameters.
  //! In particular we have (IEC 60559):
  //!
  //!  *  pow_abs($\pm0$, y), where y is a negative odd integer, returns $+\infty$.
  //!  *  pow_abs($\pm0$, y), where y is negative, finite, and is an even integer or a non-integer, returns $+\infty$.
  //!  *  pow_abs($\pm0$, $-\infty$) returns $+\infty$.
  //!  *  pow_abs($\pm0$, y), where y is a positive odd integer, returns $+0$.
  //!  *  pow_abs($\pm0$, y), where y is positive non-integer or a positive even integer, returns $+0$.
  //!  *  pow_abs(-1, $\pm\infty$) returns 1.
  //!  *  pow_abs($\pm1$, y) returns 1 for any y, even when y is NaN.
  //!  *  pow_abs(x, $\pm0$) returns 1 for any x, even when x is NaN.
  //!  *  pow_abs(x, $-\infty$) returns $+\infty$ for any |x| `<` 1.
  //!  *  pow_abs(x, $-\infty$) returns $+0$ for any |x| `>` 1.
  //!  *  pow_abs(x, $+\infty$) returns $+0$ for any |x| `<` 1.
  //!  *  pow_abs(x, $+\infty$) returns $+\infty$ for any |x| `>` 1.
  //!  *  pow_abs($+\infty$, y) returns $+0$ for any negative y.
  //!  *  pow_abs($+\infty$, y) returns $+\infty$ for any positive y.
  //!  *  except where specified above, if any argument is NaN, NaN is returned.
  //!
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::pow_abs
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `pow_abs[cond](x, ...)` is equivalent to `if_else(cond,pow_abs(x, ...),x)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  ====================================================================================================
  //!  * `raw`
  //!     The expression `raw(pow_abs)(x,y)` merely returns `exp(y*log(|x|)` which is must faster way to compute the result
  //!      than the regular implemention, but does not fullfill all the boundary requisites of IEC 60559 and has not always a good accuracy.
  //!  
  //!  * `diff`
  //!     **Required header: 
  //!      ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!       #include <eve/function/diff/pow.hpp>`
  //!      ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!  
  //!     The expression `diff_1st(pow_abs)(x,y)` and `diff_2nd(pow_abs)(x,y)` computes the partial
  //!      diffs of $f$, where $f$ is the function $(x,y) \rightarrow \ |x|^y$.
  //!  
  //!
  //! #### Example
  //!
  //! [**See it live on Compiler Explorer**](https://godbolt.org/z/TODO)
  //!
  //! @include{lineno} doc/core/pow_abs.cpp
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(pow_abs_, pow_abs);
}

#include <eve/module/real/math/function/regular/generic/pow_abs.hpp>


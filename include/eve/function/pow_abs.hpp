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
  //! @brief Callable object computing the pow_abs function \f$|x|^y\f$.
  //!
  //! **Required header:** `#include <eve/function/pow_abs.hpp>`
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
  //!`x`:   [value](@ref eve::value).
  //!
  //!`y`:   [real value](@ref eve::real_value).
  //!
  //! **Return value**
  //!
  //!Returns [element-wise](@ref glossary_elementwise) \f$|x|^y\f$.
  //!
  //! The result type is the [common compatible type](@ref common_compatible) of the two parameters.
  //! In particular we have (IEC 60559):
  //!
  //!  *  pow_abs(\f$\pm0\f$, y), where y is a negative odd integer, returns \f$+\infty\f$.
  //!  *  pow_abs(\f$\pm0\f$, y), where y is negative, finite, and is an even integer or a non-integer, returns \f$+\infty\f$.
  //!  *  pow_abs(\f$\pm0\f$, \f$-\infty\f$) returns \f$+\infty\f$.
  //!  *  pow_abs(\f$\pm0\f$, y), where y is a positive odd integer, returns \f$+0\f$.
  //!  *  pow_abs(\f$\pm0\f$, y), where y is positive non-integer or a positive even integer, returns \f$+0\f$.
  //!  *  pow_abs(-1, \f$\pm\infty\f$) returns 1.
  //!  *  pow_abs(\f$\pm1\f$, y) returns 1 for any y, even when y is NaN.
  //!  *  pow_abs(x, \f$\pm0\f$) returns 1 for any x, even when x is NaN.
  //!  *  pow_abs(x, \f$-\infty\f$) returns \f$+\infty\f$ for any |x| `<` 1.
  //!  *  pow_abs(x, \f$-\infty\f$) returns \f$+0\f$ for any |x| `>` 1.
  //!  *  pow_abs(x, \f$+\infty\f$) returns \f$+0\f$ for any |x| `<` 1.
  //!  *  pow_abs(x, \f$+\infty\f$) returns \f$+\infty\f$ for any |x| `>` 1.
  //!  *  pow_abs(\f$+\infty\f$, y) returns \f$+0\f$ for any negative y.
  //!  *  pow_abs(\f$+\infty\f$, y) returns \f$+\infty\f$ for any positive y.
  //!  *  except where specified above, if any argument is NaN, NaN is returned.
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
  //!  * eve::raw
  //!     The expression `raw(pow_abs)(x,y)` merely returns `exp(y*log(|x|)` which is must faster way to compute the result
  //!      than the regular implemention, but does not fullfill all the boundary requisites of IEC 60559 and has not always a good accuracy.
  //!
  //!  * eve::diff_1st, eve::diff_2nd
  //!
  //!     **Required header:** `#include <eve/function/diff/pow.hpp>`
  //!
  //!     The expression `diff_1st(pow_abs)(x,y)` and `diff_2nd(pow_abs)(x,y)` computes the partial
  //!      derivatives of \f$f\f$, where \f$f\f$ is the function \f$(x,y) \rightarrow \ |x|^y\f$.
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

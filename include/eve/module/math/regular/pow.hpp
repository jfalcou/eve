//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup math_exp
  //! @{
  //! @var pow
  //!
  //! @brief Callable object computing the pow operation \f$x^y\f$.
  //!
  //!   **Defined in Header**
  //!
  //!   @code
  //!   #include <eve/module/math.hpp>
  //!   @endcode
  //!
  //!   @groupheader{Callable Signatures}
  //!
  //!   @code
  //!   namespace eve
  //!   {
  //!      template< eve::floating_value T, eve::floating_value U >
  //!      T pow(T x, U y) noexcept;
  //!   }
  //!   @endcode
  //!
  //! **Parameters**
  //!
  //!`x`, `y`:   [values](@ref eve::value).
  //!
  //! **Return value**
  //!
  //!Returns [elementwise](@ref glossary_elementwise) \f$x^y\f$.
  //!
  //! The result type is the [common compatible type](@ref common_compatible) of the two parameters.
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
  //!  @groupheader{Semantic Modifiers}
  //!
  //!   * Masked Call
  //!
  //!     The call `eve;::pow[mask](x, y)` provides a masked version of `eve::pow` which is
  //!     equivalent to `if_else (mask, pow(x, y), x)`.
  //!
  //!      **Example**
  //!
  //!        @godbolt{doc/math/masked/pow.cpp}
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(pow_, pow);
}

#include <eve/module/math/regular/impl/pow.hpp>

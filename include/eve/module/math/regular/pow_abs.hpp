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
//! @var pow_abs
//!
//! @brief Callable object computing the pow_abs function \f$|x|^y\f$.
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
//!      auto pow_absm1(T x, U y) noexcept;                                 //1
//!
//!      template< eve::floating_value T, eve::floating_value U >           //2
//!      auto pow_absm1(eve::as_complex_t<T> x, U y) noexcept;
//!
//!      template< eve::floating_value T, eve::floating_value U >           //2
//!      auto pow_absm1(T x, eve::as_complex_t<U> y) noexcept;
//!
//!      template< eve::floating_value T, eve::floating_value U >
//!      auto pow_absm1(eve::as_complex_t<T> x, eve::as_complex_t<U> y) noexcept; //2
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!    `x`, `y`:   [real floating](@ref eve::floating_value) or [complex ](@ref eve::complex) arguments.
//!
//! **Return value**
//!
//! Returns [elementwise](@ref glossary_elementwise) \f$|x|^y\f$.
//!
//! The result type is the [common value type](@ref common_value) of the two parameters.
//! In particular we have (IEC 60559) for floating entries:
//!
//!  *  pow_abs(\f$\pm0\f$, y), where y is a negative odd integer, returns \f$+\infty\f$.
//!  *  pow_abs(\f$\pm0\f$, y), where y is negative, finite, and is an even integer or a
//!  non-integer, returns \f$+\infty\f$.
//!  *  pow_abs(\f$\pm0\f$, \f$-\infty\f$) returns \f$+\infty\f$.
//!  *  pow_abs(\f$\pm0\f$, y), where y is a positive odd integer, returns \f$+0\f$.
//!  *  pow_abs(\f$\pm0\f$, y), where y is positive non-integer or a positive even integer, returns
//!  \f$+0\f$.
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
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/pow_abs.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::pow_abs[mask](x, y)` provides a masked version of `eve::pow_abs` which is
//!     equivalent to `if_else (mask, pow_abs(x, y), x)`.
//!
//!      **Example**
//!
//!        @godbolt{doc/math/masked/pow_abs.cpp}
//!  @}
//================================================================================================
EVE_MAKE_CALLABLE(pow_abs_, pow_abs);
}

#include <eve/module/math/regular/impl/pow_abs.hpp>

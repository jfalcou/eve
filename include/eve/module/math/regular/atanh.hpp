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
//! @addtogroup math_invhyper
//! @{
//! @var atanh
//!
//! @brief Callable object computing \f$\frac{1}{2}\log((1+x)/(1-x))\f$.
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
//!      template< eve::floating_value T >
//!      T atanh(T x) noexcept;                                    //1
//!
//!      template< eve::floating_value T >
//!      eve::complex<T> atanh(eve::complex<T> z) noexcept;        //2
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!   *  `x`:   [floating real value](@ref eve::floating_ordered_value).
//!   *  `z`:   [complex ](@ref eve::complex) value.
//!
//! **Return value**
//!
//!   1. Returns the [elementwise](@ref glossary_elementwise) inverse hyperbolic cotangent of the input.
//!      The inverse hyperbolic sine is semantically equivalent to \f$\frac{1}{2}\log((1+x)/(1-x))\f$.
//!
//!      In particular:
//!
//!      * If the element is \f$\pm1\f$, \f$\pm\infty\f$ is returned.
//!      * If the element is \f$\pm0\f$, \f$\pm0\f$ is returned.
//!      * If the element is greater than one or a `NaN`, `NaN` is returned.
//!
//!    2. Returns the complex arc hyperbolic sine of z, in the range of a half-strip mathematically
//!       unbounded along the real axis and in the interval  \f$i\times[-\pi/2, \pi/2]\f$ along
//!       the imaginary axis.
//!
//!       * for every z: eve::atanh(eve::conj(z)) == eve::conj(std::atanh(z))
//!       * for every z: eve::atanh(-z) == -eve::atanh(z)
//!       * If z is \f$+0\f$, the result is \f$+0\f$
//!       * If z is \f$NaN\f$, the result is \f$NaN\f$
//!       * If z is \f$+1\f$, the result is \f$+\infty\f$
//!       * If z is \f$x+i \infty\f$ (for any finite positive x), the result is \f$+0,\pi/2\f$
//!       * If z is \f$x+i NaN\f$ (for any finite nonzero x),  the result is \f$NaN+i NaN\f$
//!       * If z is \f$+\infty+i y\f$ (for any finite positive y),  the result is \f$i \pi/2\f$
//!       * If z is \f$+\infty+i \infty\f$, the result is \f$i \pi/2\f$
//!       * If z is \f$+\infty+i NaN\f$,  the result is \f$i NaN\f$
//!       * If z is \f$NaN+i y\f$ (for any finite y), the result is \f$NaN+i NaN\f$
//!       * If z is \f$NaN+i \infty\f$, the result is \f$i \pi/2\f$ (the sign of the real part is unspecified)
//!       * If z is \f$NaN+i NaN\f$,  the result is \f$NaN+i NaN\f$
//!
//!  @groupheader{Example}
//!
//!   **Real version**
//!
//!  @godbolt{doc/math/regular/atanh.cpp}
//!
//!   **Complex version**
//!
//!  @godbolt{doc/complex/regular/atanh.cpp}
//!  @}
//================================================================================================
namespace tag
{
  struct atanh_;
}

template<> struct supports_optimized_conversion<tag::atanh_> : std::true_type
{};

  EVE_MAKE_CALLABLE(atanh_, atanh);
}

#include <eve/module/math/regular/impl/atanh.hpp>

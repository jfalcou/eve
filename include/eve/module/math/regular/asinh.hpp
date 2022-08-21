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
//! @var asinh
//!
//! @brief Callable object computing \f$\log(x+\sqrt{x^2+1})\f$.
//!
//!   **Defined in Header**
//!
//!   @code
//!   #include <eve/module/math.hpp>
//!   @endcode
//!
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      template< eve::floating_value T >
//!      T asinh(T x) noexcept;                                    //1
//!
//!      template< eve::floating_value T >
//!      eve::complex<T> asinh(eve::complex<T> z) noexcept;        //2
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!   *  `x`:   [floating real value](@ref eve::floating_real_value).
//!   *  `z`:   [complex ](@ref eve::complex) value.
//!
//! **Return value**
//!
//!   1. Returns the [elementwise](@ref glossary_elementwise) inverse hyperbolic cosine of the input.
//!      The inverse hyperbolic sine is semantically equivalent to \f$\log(x+\sqrt{x^2+1})\f$.
//!
//!      In particular:
//!
//!      * If the element is \f$\pm0\f$, \f$\pm0\f$ is returned.
//!      * If the element is \f$\pm\infty\f$, \f$\pm\infty\f$ returned.
//!      * If the element is a `NaN`, `NaN` is returned.
//!
//!    2. Returns the complex arc hyperbolic sine of z, with branch cuts outside the interval
//!       \f$i\times[-\pi/2, \pi/2]\f$ along the imaginary axis.
//!
//!       * for every z: eve::asinh(eve::conj(z)) == eve::conj(std::asinh(z))
//!       * for every z: eve::asinh(-z) == -eve::asinh(z)
//!       * If z is \f$+0\f$, the result is \f$+0\f$
//!       * If z is \f$x+i \infty\f$ (for any positive finite x), the result is \f$+\infty+i \pi/2\f$
//!       * If z is \f$x,NaN\f$ (for any finite x), the result is \f$NaN+ iNaN\f$
//!       * If z is \f$+\infty+ iy\f$ (for any positive finite y), the result is \f$+\infty+i 0\f$
//!       * If z is \f$+\infty+i \infty\f$, the result is \f$+\infty+ i\pi/4\f$
//!       * If z is \f$+\infty+ iNaN\f$, the result is \f$+\infty+ iNaN\f$
//!       * If z is \f$NaN+i 0\f$, the result is \f$NaN+i 0\f$
//!       * If z is \f$NaN+ iy\f$ (for any finite nonzero y), the result is \f$NaN+ iNaN\f$
//!       * If z is \f$NaN+i \infty\f$, the result is \f$\pm \infty+ iNaN\f$ (the sign of the real part is unspecified)
//!       * If z is \f$NaN+ iNaN\f$, the result is \f$NaN+ iNaN\f$
//!
//!  @groupheader{Example}
//!
//!   **Real version**
//!
//!  @godbolt{doc/math/asinh.cpp}
//!
//!   **Complex version**
//!
//!  @godbolt{doc/complex/asinh.cpp}
//!  @}
//================================================================================================
EVE_MAKE_CALLABLE(asinh_, asinh);
}

#include <eve/module/math/regular/impl/asinh.hpp>

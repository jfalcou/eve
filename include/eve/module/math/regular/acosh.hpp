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
//! @var acosh
//!
//! @brief Callable object computing  \f$\log(x+\sqrt{x^2-1})\f$.
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
//!      T acosh(T x) noexcept;                                    //1
//!
//!      template< eve::floating_value T >
//!      eve::complex<T> acosh(eve::complex<T> z) noexcept;        //2
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
//!   1. Returns the [elementwise](@ref glossary_elementwise) inverse hyperbolic cosine of the input.
//!      For values in the domain `x>1`, the inverse hyperbolic cosine is semantically equivalent to
//!      \f$\log(x+\sqrt{x^2-1})\f$.
//!
//!      In particular:
//!
//!      * If the element is less than \f$1\f$ or `Nan`, `NaN` is returned.
//!      * If the element is \f$1\f$, \f$+0\f$ is returned.
//!      * If the element is \f$+\infty\f$, \f$+\infty\f$ is returned.
//!      * If the element is a `Nan`, `NaN` is returned.
//!
//!   2. Returns the complex arc hyperbolic cosine of z, in the range of a
//!      strip unbounded along the imaginary axis and
//!      in the interval \f$[0,\pi]\f$ along the real axis.
//!
//!      * for every z: eve::acosh(eve::conj(z)) == eve::conj(std::acosh(z))
//!      * If z is \f$\pm0\f$, the result is \f$i pi/2\f$
//!      * If z is \f$\pm0\f$, the result is \f$+0,\pi/2\f$
//!      * If z is \f$x+i\infty\f$ (for any finite x), the result is \f$\infty+i\pi/2\f$
//!      * If z is \f$x+i NaN\f$ (for any finite non zero x), the result is \f$NaN+i NaN\f$.
//!      * If z is \f$i NaN\f$  the result is \f$NaN+i\pi/2\f$.
//!      * If z is \f$-\infty,y\f$ (for any positive finite y), the result is \f$+\infty,\pi\f$
//!      * If z is \f$+\infty,y\f$ (for any positive finite y), the result is \f$+\infty+i 0\f$
//!      * If z is \f$-\infty+i \infty\f$, the result is \f$+\infty,3\pi/4\f$
//!      * If z is \f$\pm\infty+i NaN\f$, the result is \f$+\infty+i NaN\f$
//!      * If z is \f$NaN,y\f$ (for any finite y), the result is \f$NaN+i NaN\f$.
//!      * If z is \f$NaN+i \infty\f$, the result is \f$+\infty+i NaN\f$
//!      * If z is \f$NaN+i NaN\f$, the result is \f$NaN+i NaN\f$
//!
//!  @groupheader{Example}
//!
//!   **Real version**
//!
//!  @godbolt{doc/math/regular/acosh.cpp}
//!
//!   **Complex version**
//!
//!  @godbolt{doc/complex/regular/acosh.cpp}
//!
//!  @}
//================================================================================================
EVE_MAKE_CALLABLE(acosh_, acosh);
}

#include <eve/module/math/regular/impl/acosh.hpp>

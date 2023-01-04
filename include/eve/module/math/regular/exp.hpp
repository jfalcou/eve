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
//! @var exp
//!
//! @brief Callable object computing \f$e^x\f$.
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
//!      T exp(T x) noexcept;                                     //1
//!
//!      template< eve::floating_value T >
//!      eve::complex<T> acos(eve::complex<T> z) noexcept;        //2
///   }
//!   @endcode
//!
//! **Parameters**
//!
//!   *  `x`:   [floating value](@ref eve::floating_value).
//!   *  `z`:   [complex ](@ref eve::complex) value.
//!
//! **Return value**
//!
//!   1. Returns the [elementwise](@ref glossary_elementwise) exponential of the input.
//!
//!     In particular:
//!
//!     * If the element is \f$\pm0\f$, \f$1\f$ is returned
//!     * If the element is \f$-\infty\f$, \f$+0\f$ is returned
//!     * If the element is \f$\infty\f$, \f$\infty\f$ is returned
//!     * If the element is a `NaN`, `NaN` is returned
//!
//!   2. Returns [elementwise](@ref glossary_elementwise) the exponential of the input.
//!
//!      * for every z: eve::exp(eve::conj(z)) == eve::conj(std::exp(z))
//!      * If z is \f$\pm0\f$, the result is \f$1\f$
//!      * If z is \f$x+i \infty\f$ (for any finite x), the result is \f$NaN+i NaN\f$.
//!      * If z is \f$x+i NaN\f$ (for any finite x), the result is \f$NaN+i NaN\f$.
//!      * If z is \f$+\infty+i 0\f$, the result is \f$+\infty\f$
//!      * If z is \f$-\infty+i y\f$ (for any finite y), the result is \f$+0 \mathrm{cis}(y)\f$.
//!      * If z is \f$+\infty+i y\f$ (for any finite nonzero y), the result is \f$+\infty \mathrm{cis}(y)\f$.
//!      * If z is \f$-\infty+i \infty\f$, the result is \f$\pm 0+i \pm 0\f$ (signs are unspecified)
//!      * If z is \f$+\infty+i \pm\infty\f$, the result is \f$\pm \infty+i NaN\f$ (the sign of the real part is unspecified).
//!      * If z is \f$-\infty+i NaN\f$, the result is \f$\pm 0+i \pm 0\f$ (signs are unspecified).
//!      * If z is \f$\pm\infty+i NaN\f$, the result is \f$\pm \infty+i NaN\f$ (the sign of the real part is unspecified).
//!      * If z is \f$NaN\f$, the result is \f$NaN\f$.
//!      * If z is \f$NaN+i y\f$ (for any nonzero y), the result is \f$NaN+i NaN\f$.
//!      * If z is \f$NaN+i NaN\f$, the result is \f$NaN+i NaN\f$.
//!
//!      where \f$\mathrm{cis}(y) = \cos(y)+i \sin(y)\f$
//!
//!  @groupheader{Example}
//!
//!   **Real version**
//!
//!  @godbolt{doc/math/regular/exp.cpp}
//!
//!   **Complex version**
//!
//!  @godbolt{doc/complex/regular/exp.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::exp[mask](x)` provides a masked version of `eve::exp` which is
//!     equivalent to `if_else (mask, exp(x), x)`.
//!
//!      **Example**
//!
//!        @godbolt{doc/math/masked/exp.cpp}
//!  @}
//================================================================================================
EVE_MAKE_CALLABLE(exp_, exp);
}

#include <eve/module/math/regular/impl/exp.hpp>

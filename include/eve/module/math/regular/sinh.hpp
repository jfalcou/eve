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
//! @addtogroup math_hyper
//! @{
//! @var sinh
//!
//! @brief Callable object computing \f$\frac{e^x-e^{-x}}2\f$.
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
//!      T sinh(T x) noexcept;
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!   *  `x`:   [floating value](@ref eve::floating_value).
//!   *  `z`:   [complex ](@ref eve::complex) value.
//!
//! **Return value**
//!
//!   1. Returns the [elementwise](@ref glossary_elementwise) hyperbolic sine of the input.
//!
//!      In particular:
//!
//!      * If the element is \f$\pm0\f$, \f$\pm0\f$ is returned.
//!      * If the element is \f$\pm\infty\f$, \f$\pm\infty\f$ returned.
//!      * If the element is a `NaN`, `NaN` is returned.
//!
//!   2. Returns [elementwise](@ref glossary_elementwise) the complex value
//!      of the hyperbolic sine of the input.
//!
//!      * for every z: `eve::sinh(eve::conj(z)) == eve::conj(std::sinh(z))`
//!      * for every z: `eve::sinh(-z)           == -eve::sinh(z)`
//!      * If z is \f$+0\f$, the result is \f$+0\f$
//!      * If z is \f$i \infty\f$, the result is \f$i NaN\f$ (the sign of the real part is unspecified)
//!      * If z is \f$i NaN\f$, the result is \f$NaN\f$
//!      * If z is \f$x+i \infty\f$ (for any positive finite x), the result is \f$NaN+i NaN\f$
//!      * If z is \f$x+i NaN\f$ (for any positive finite x), the result is \f$NaN+i NaN\f$
//!      * If z is \f$+\infty\f$, the result is \f$+\infty\f$
//!      * If z is \f$+\infty+i y\f$ (for any positive finite y), the result is \f$\infty\times cis(y)\f$
//!      * If z is \f$+\infty+i \infty\f$, the result is \f$\pm \infty+i NaN\f$ (the sign of the real part is unspecified)
//!      * If z is \f$+\infty+i NaN\f$, the result is \f$\pm \infty+i NaN\f$ (the sign of the real part is unspecified)
//!      * If z is \f$NaN\f$, the result is \f$NaN\f$
//!      * If z is \f$NaN+i y\f$ (for any finite nonzero y), the result is \f$NaN+i NaN\f$
//!
//!      where \f$\mathrm{cis}(y) =  \cos(y)+i\sin(y)\f$
//!
//!    **Real version**
//!
//!  @godbolt{doc/math/sinh.cpp}
//!
//!   **Complex version**
//!
//!  @godbolt{doc/complex/sinh.cpp}
//!
//!  @}
//================================================================================================
EVE_MAKE_CALLABLE(sinh_, sinh);
}

#include <eve/module/math/regular/impl/sinh.hpp>

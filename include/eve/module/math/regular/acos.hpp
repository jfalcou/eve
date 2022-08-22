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
//! @addtogroup math_invtrig
//! @{
//! @var acos
//!
//! @brief Callable object computing the arc cosine.
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
//!      T acos(T x) noexcept;                                    //1
//!
//!      template< eve::floating_value T >
//!      eve::complex<T> acos(eve::complex<T> z) noexcept;        //2
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
//!   1. Returns the [elementwise](@ref glossary_elementwise) arc cosine of the
//!      input in the range \f$[0 , \pi]\f$.
//!
//!      In particular:
//!
//!      * If the element is \f$1\f$, \f$+0\f$ is returned.
//!      * If the element \f$|x| > 1\f$, `NaN` is returned.
//!      * If the element is a `Nan`, `NaN` is returned.
//!
//!   2. Returns [elementwise](@ref glossary_elementwise) the complex principal value
//!      of the arc cosine of the input.
//!      Branch cuts exist outside the interval \f$[-1, +1]\f$ along the real axis.
//!
//!      * for every z: eve::acos(eve::conj(z)) == eve::conj(std::acos(z))
//!      * If z is \f$\pm0\f$, the result is \f$\pi/2\f$
//!      * If z is \f$i NaN\f$, the result is \f$\pi/2+ i NaN\f$
//!      * If z is \f$x+i\infty\f$ (for any finite x), the result is \f$\pi/2-i\infty\f$
//!      * If z is \f$x+i NaN\f$ (for any nonzero finite x), the result is \f$NaN+i NaN\f$.
//!      * If z is \f$-\infty+i y\f$ (for any positive finite y), the result is \f$\pi-i\infty\f$
//!      * If z is \f$+\infty+i y\f$ (for any positive finite y), the result is \f$+0-i\infty\f$
//!      * If z is \f$-\infty+i +\infty\f$, the result is \f$3\pi/4-i\infty\f$
//!      * If z is \f$\infty+i +\infty\f$, the result is \f$\pi/4-i\infty\f$
//!      * If z is \f$\pm\infty+i NaN\f$, the result is \f$NaN \pm i\infty\f$ (the sign
//!        of the imaginary part is unspecified)
//!      * If z is \f$NaN+i y\f$ (for any finite y), the result is \f$NaN+i NaN\f$
//!      * If z is \f$NaN+i\infty\f$, the result is \f$NaN-i\infty\f$
//!      * If z is \f$NaN+i NaN\f$, the result is \f$NaN+i NaN\f$
//!
//!  @groupheader{Example}
//!
//!   **Real version**
//!
//!  @godbolt{doc/math/acos.cpp}
//!
//!   **Complex version**
//!
//!  @godbolt{doc/complex/acos.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!  * eve::raw
//!     The call `raw(acos)(x)`, call a faster implementation for
//!     [floating real values](@ref floating_value) which can be slightly less accurate near 1.
//!  @}
//================================================================================================

EVE_MAKE_CALLABLE(acos_, acos);
}

#include <eve/module/math/regular/impl/acos.hpp>

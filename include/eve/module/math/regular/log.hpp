//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/detail/overload.hpp>

namespace eve
{
//================================================================================================
//! @addtogroup math_log
//! @{
//! @var log
//!
//! @brief Callable object computing the natural logarithm: \f$\log x\f$.
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
//!      T log(T x) noexcept;                                    //1
//!
//!      template< eve::floating_value T >
//!      eve::complex<T> log(eve::complex<T> z) noexcept;        //2
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
//!   1. Returns the [elementwise](@ref glossary_elementwise) the natural
//!      logarithm  of `x`: \f$\log x\f$.
//!
//!      * If the element is \f$\pm0\f$, \f$-\infty\f$ is returned.
//!      * If the element is \f$1\f$, \f$+0\f$ is returned.
//!      * If the element is \f$\infty\f$, \f$\infty\f$ is returned.
//!      * If the element is less than 0, `NaN` is returned.
//!
//!   2. Returns [elementwise](@ref glossary_elementwise) the natural logarithm of the input
//!      in the range of a strip in the interval \f$i\times[-\pi, \pi]\f$ along the imaginary axis
//!      and mathematically unbounded along the real axis. .
//!
//!      * The function is continuous onto the branch cut  along the negative real axis,
//!        taking into account the sign of imaginary part
//!      * for every z: `eve::log(eve::conj(z)) == eve::conj(eve::log(z))`
//!      * If z is \f$-0\f$, the result is \f$-\infty+i \pi \f$
//!      * If z is \f$+0\f$, the result is \f$-\infty\f$
//!      * If z is \f$x+i \infty\f$ (for any finite x), the result is \f$+\infty+i \pi/2\f$
//!      * If z is \f$x+i NaN\f$ (for any finite x), the result is \f$NaN+i NaN\f$
//!      * If z is \f$-\infty+i y\f$ (for any finite positive y), the result is \f$+\infty+i \pi \f$
//!      * If z is \f$+\infty+i y\f$ (for any finite positive y), the result is \f$+\infty\f$
//!      * If z is \f$-\infty+i \infty\f$, the result is \f$+\infty+i 3\pi/4\f$
//!      * If z is \f$+\infty+i \infty\f$, the result is \f$+\infty+i \pi/4\f$
//!      * If z is \f$\pm\infty+i NaN\f$, the result is \f$+\infty+i NaN\f$
//!      * If z is \f$NaN+i y\f$ (for any finite y), the result is \f$NaN+i NaN\f$
//!      * If z is \f$NaN+i \infty\f$, the result is \f$+\infty+i NaN\f$
//!      * If z is \f$NaN+i NaN\f$, the result is \f$NaN+i NaN\f$
//!
//!  @groupheader{Example}
//!
//!   **Real version**
//!
//!  @godbolt{doc/math/log.cpp}
//!
//!   **Complex version**
//!
//!  @godbolt{doc/complex/log.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::log[mask](x)` provides a masked version of `eve::log` which is
//!     equivalent to `if_else (mask, log(x), x)`.
//!
//!      **Example**
//!
//!        @godbolt{doc/math/masked/log.cpp}
//!  @}
//================================================================================================
EVE_MAKE_CALLABLE(log_, log);
}

#include <eve/module/math/regular/impl/log.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/math/regular/impl/simd/x86/log.hpp>
#endif

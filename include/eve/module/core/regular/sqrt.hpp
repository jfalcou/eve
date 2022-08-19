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

#include <type_traits>

namespace eve
{
//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var sqrt
//!   @brief Computes the square root of the parameter.
//!
//!   **Defined in Header**
//!
//!   @code
//!   #include <eve/module/core.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      template< eve::floating_value T >
//!      T sqrt(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [real](@ref eve::floating_value) argument.
//!     * `z` :  [complex](@ref eve::complex) argument.
//!
//!   **Return value**
//!
//!     1. value containing the [elementwise](@ref glossary_elementwise)
//!        square root of `x` or Nan if `x` is less than zero.
//!
//!     2. Returns the [elementwise](@ref glossary_elementwise) the square root of z,
//!        in the range of the right half-plane, including the imaginary axis (\f$[0, +\infty]\f$
//!        along the real axis and \f$[-\infty, +\infty]\f$ along the imaginary axis.)
//!
//!        *  The function is continuous onto the branch cut taking into account
//!           the sign of imaginary part
//!        *  eve::sqrt(eve::conj(z)) == eve::conj(eve::sqrt(z))
//!        *  If z is \f$\pm0\f$, the result is \f$+0\f$
//!        *  If z is \f$x+i \infty\f$, the result is \f$\infty+i \infty\f$ even if x is \f$NaN\f$
//!        *  If z is \f$x,NaN\f$, the result is \f$NaN,NaN\f$ (unless x is \f$\pm\infty\f$)
//!        *  If z is \f$-\infty+i y\f$, the result is \f$+0+i \infty\f$ for finite positive y
//!        *  If z is \f$+\infty+i y\f$, the result is \f$+\infty+i 0\f$ for finite positive y
//!        *  If z is \f$-\infty+i NaN\f$, the result is \f$NaN \pm i \infty\f$ (sign of imaginary part unspecified)
//!        *  If z is \f$+\infty+i NaN\f$, the result is \f$+\infty+i NaN\f$
//!        *  If z is \f$NaN+i y\f$, the result is \f$NaN+i NaN\f$
//!        *  If z is \f$NaN+i NaN\f$, the result is \f$NaN+i NaN\f$
//!
//!  @groupheader{Example}
//!
//!   **real version**
//!
//!  @godbolt{doc/core/regular/sqrt.cpp}
//!
//!   **complex version**
//!
//!  @godbolt{doc/complex/sqrt.cpp}
//!
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve;::sqrt[mask](x)` provides a masked version of `eve::sqrt` which is
//!     equivalent to `if_else (mask, sqrt(x), x)`.
//!
//!      **Example**
//!
//!        @godbolt{doc/core/masked/sqrt.cpp}
//!
//!  * eve::raw
//!     The call `raw(sqrt)(x)`, call a proper system intrinsic if one exists, but with possibly
//!     very poor accuracy in return.
//!      Otherwise it uses the non-decorated call.
//!
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(sqrt_, sqrt);
}

#include <eve/arch.hpp>
#include <eve/module/core/regular/impl/sqrt.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/sqrt.hpp>
#endif

#if defined(EVE_INCLUDE_POWERPC_HEADER)
#  include <eve/module/core/regular/impl/simd/ppc/sqrt.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/neon/sqrt.hpp>
#endif

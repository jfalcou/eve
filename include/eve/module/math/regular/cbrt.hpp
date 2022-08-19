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
//! @var cbrt
//!
//! @brief Callable object computing the cubic root.
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
//!      T cbrt(T x) noexcept;
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!     * `x` :  [real](@ref eve::value) or [complex](@ref eve::complex) argument.
//!
//! **Return value**
//!
//!   Returns a [elementwise](@ref glossary_elementwise) cubic root value of the input.
//!
//!   @warning
//!      cbrt for complex inputs is NOT eve::pow(x, eve:third(as(x))). It only provides an extension
//!      to the complex plane of the real cbrt. The branch cut is \f$[-\infty, \infty]-\{0}\f$
//!      along he imaginary axis  and fold the left half-plane towards the negative real axis
//!      and the right half-plane towards the positive real axis.
//!      All this being non standard.
//!
//!  @groupheader{Example}
//!
//!   **real version**
//!
//!  @godbolt{doc/math/cbrt.cpp}
//!
//!   **complex version**
//!
//!  @godbolt{doc/complex/cbrt.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::cbrt[mask](x)` provides a masked version of `eve::cbrt` which is
//!     equivalent to `if_else (mask, abs(x), x)`.
//!
//!      **Example**
//!
//!        @godbolt{doc/core/masked/cbrt.cpp}
//!  @}
//================================================================================================
EVE_MAKE_CALLABLE(cbrt_, cbrt);
}

#include <eve/module/math/regular/impl/cbrt.hpp>
